/* match.c
 * Simple token-based matching between lost and found items.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "match.h"
#include "lost.h"
#include "found.h"
#include "fileops.h"

/* small stopword list to ignore common short words */
static const char *stopwords[] = {
    "the","a","an","and","or","with","of","in","on","at","for","to","by","from","is","it", NULL
};

/* is_stopword: return 1 if w is in stopwords */
static int is_stopword(const char *w) {
    for (int i = 0; stopwords[i]; ++i) {
        if (strcmp(stopwords[i], w) == 0) return 1;
    }
    return 0;
}

/* normalize_and_split:
 * Lower-case, convert punctuation to spaces, then tokenize by spaces.
 * tokens is an array of token buffers; tn receives token count.
 */
static void normalize_and_split(const char *s, char tokens[][40], int *tn) {
    char tmp[512];
    int k = 0;
    for (int i = 0; s[i] && k < (int)sizeof(tmp)-1; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (isalnum(c) || c == ' ') tmp[k++] = (char)tolower(c);
        else tmp[k++] = ' ';
    }
    tmp[k] = '\0';
    *tn = 0;
    char *p = strtok(tmp, " ");
    while (p && *tn < 50) {
        if (!is_stopword(p) && strlen(p) >= 2) {
            strncpy(tokens[*tn], p, 39);
            tokens[*tn][39] = '\0';
            (*tn)++;
        }
        p = strtok(NULL, " ");
    }
}

/* simple_score: count overlapping tokens (rough similarity) */
static int simple_score(const char *a, const char *b) {
    if (!a || !b) return 0;
    char atoks[50][40], btoks[50][40];
    int an = 0, bn = 0;
    normalize_and_split(a, atoks, &an);
    normalize_and_split(b, btoks, &bn);
    int score = 0;
    for (int i = 0; i < an; ++i) {
        for (int j = 0; j < bn; ++j) {
            if (strstr(btoks[j], atoks[i]) || strstr(atoks[i], btoks[j])) {
                score++;
                break;
            }
        }
    }
    return score;
}

/* match_lost_and_found:
 * Loads both DBs and prints candidate pairs with score > 0.
 * Returns 0 on success, -1 on error.
 */
int match_lost_and_found(const char *lost_file, const char *found_file) {
    LostItem *lost = NULL; int ln = 0;
    FoundItem *found = NULL; int fn = 0;

    if (load_lost_items(lost_file, &lost, &ln) < 0) { printf("Error loading lost items\n"); return -1; }
    if (load_found_items(found_file, &found, &fn) < 0) { if (lost) free(lost); printf("Error loading found items\n"); return -1; }

    if (ln == 0 || fn == 0) {
        printf("No items to match.\n");
        if (lost) free(lost);
        if (found) free(found);
        return 0;
    }

    printf("Potential Matches (score > 0):\n");
    for (int i = 0; i < ln; ++i) {
        for (int j = 0; j < fn; ++j) {
            int score = simple_score(lost[i].description, found[j].description)
                      + simple_score(lost[i].name, found[j].name);
            if (score > 0) {
                printf("Lost ID %d <--> Found ID %d | score=%d\n  Lost: %s\n  Found: %s\n\n",
                       lost[i].id, found[j].id, score, lost[i].description, found[j].description);
            }
        }
    }

    free(lost);
    free(found);
    return 0;
}
