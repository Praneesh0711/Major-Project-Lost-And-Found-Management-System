/* found.c
 * Implements add/list/search for found items.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "found.h"
#include "fileops.h"
#include "utils.h"

/* Helper: find next available ID (max existing id + 1) */
static int next_found_id(FoundItem *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; ++i) if (arr[i].id > max) max = arr[i].id;
    return max + 1;
}

/* add_found_item:
 * Append a FoundItem to the file (reads all, appends, writes back).
 * Returns 0 on success, -1 on failure.
 */
int add_found_item(const FoundItem *it, const char *filename) {
    FoundItem *arr = NULL; int n = 0;
    if (load_found_items(filename, &arr, &n) < 0) { if (arr) free(arr); return -1; }

    FoundItem *tmp = (FoundItem*)realloc(arr, sizeof(FoundItem) * (n + 1));
    if (!tmp) { free(arr); return -1; }
    tmp[n] = *it;
    tmp[n].id = next_found_id(tmp, n);
    n++;
    int res = save_found_items(filename, tmp, n);
    free(tmp);
    return res;
}

/* list_found_items:
 * Load found items and print them to console in readable form.
 * Returns 0 on success, -1 on error.
 */
int list_found_items(const char *filename) {
    FoundItem *arr = NULL; int n = 0;
    if (load_found_items(filename, &arr, &n) < 0) { printf("Error loading found items.\n"); return -1; }
    if (n == 0) { printf("--- No found items ---\n"); if (arr) free(arr); return 0; }
    printf("Found Items (%d):\n", n);
    for (int i = 0; i < n; ++i) {
        printf("ID:%d | Finder:%s | Cat:%s | Loc:%s | Date:%s\n Desc: %s\n\n",
               arr[i].id, arr[i].name, arr[i].category, arr[i].location, arr[i].date, arr[i].description);
    }
    free(arr);
    return 0;
}

/* search_found_items:
 * Search for keyword in name, category or description (simple substring search).
 * Returns number of matches found (>=0), -1 on error.
 */
int search_found_items(const char *filename, const char *keyword) {
    FoundItem *arr = NULL; int n = 0;
    if (load_found_items(filename, &arr, &n) < 0) { printf("Error loading found items.\n"); return -1; }
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if ((arr[i].name && strstr(arr[i].name, keyword)) ||
            (arr[i].description && strstr(arr[i].description, keyword)) ||
            (arr[i].category && strstr(arr[i].category, keyword))) {
            printf("ID:%d | Finder:%s | Cat:%s | Loc:%s | Date:%s\n Desc: %s\n\n",
                   arr[i].id, arr[i].name, arr[i].category, arr[i].location, arr[i].date, arr[i].description);
            found++;
        }
    }
    if (!found) printf("No found items matched '%s'\n", keyword);
    free(arr);
    return found;
}
