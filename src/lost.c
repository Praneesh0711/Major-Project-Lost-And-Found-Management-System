/* lost.c
 * Implements functions to add, list, and search lost items.
 * Uses fileops to persist items to disk.
 */

#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, realloc, free
#include <string.h>   // strlen, strcpy
#include "lost.h"     // LostItem type and prototypes
#include "fileops.h"  // load/save functions
#include "utils.h"    // helper functions and sizes

#define LOST_DB_FILENAME "lost.db" // default database filename (used by callers)

/* Helper: find next available ID (max existing id + 1) */
static int next_lost_id(LostItem *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; ++i) if (arr[i].id > max) max = arr[i].id;
    return max + 1;
}

/* add_lost_item:
 * Append a LostItem to the file (reads all, appends, writes back).
 * Returns 0 on success, -1 on failure.
 */
int add_lost_item(const LostItem *it, const char *filename) {
    LostItem *arr = NULL; int n = 0;
    if (load_lost_items(filename, &arr, &n) < 0) { if (arr) free(arr); return -1; }

    LostItem *tmp = (LostItem*)realloc(arr, sizeof(LostItem) * (n + 1)); // expand array
    if (!tmp) { free(arr); return -1; }
    // copy the provided item and assign ID
    tmp[n] = *it;
    tmp[n].id = next_lost_id(tmp, n); // assign unique id
    n++;
    int res = save_lost_items(filename, tmp, n); // persist to disk
    free(tmp);
    return res;
}

/* list_lost_items:
 * Load lost items and print them to console in readable form.
 * Returns 0 on success, -1 on error.
 */
int list_lost_items(const char *filename) {
    LostItem *arr = NULL; int n = 0;
    if (load_lost_items(filename, &arr, &n) < 0) { printf("Error loading lost items.\n"); return -1; }
    if (n == 0) { printf("--- No lost items ---\n"); if (arr) free(arr); return 0; }
    printf("Lost Items (%d):\n", n);
    for (int i = 0; i < n; ++i) {
        // print every field, user-friendly
        printf("ID:%d | Reporter:%s | Cat:%s | Loc:%s | Date:%s\n Desc: %s\n\n",
               arr[i].id, arr[i].name, arr[i].category, arr[i].location, arr[i].date, arr[i].description);
    }
    free(arr);
    return 0;
}

/* search_lost_items:
 * Search for keyword in name, category or description (case-sensitive simple search).
 * Returns number of matches found (>=0), -1 on error.
 */
int search_lost_items(const char *filename, const char *keyword) {
    LostItem *arr = NULL; int n = 0;
    if (load_lost_items(filename, &arr, &n) < 0) { printf("Error loading lost items.\n"); return -1; }
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (strstr(arr[i].name, keyword) || strstr(arr[i].description, keyword) || strstr(arr[i].category, keyword)) {
            printf("ID:%d | Reporter:%s | Cat:%s | Loc:%s | Date:%s\n Desc: %s\n\n",
                   arr[i].id, arr[i].name, arr[i].category, arr[i].location, arr[i].date, arr[i].description);
            found++;
        }
    }
    if (!found) printf("No lost items matched '%s'\n", keyword);
    free(arr);
    return found;
}
