/* fileops.c
 * Binary save/load operations for LostItem and FoundItem arrays.
 * File format:
 *   [int count] [item0][item1]...[itemN-1]
 */

#include <stdio.h>   // FILE, fopen, fwrite, fread, fclose
#include <stdlib.h>  // malloc, free
#include "fileops.h" // function prototypes and item types

/* save_lost_items:
 * Write an array of LostItem objects to filename in binary.
 * Returns 0 on success, -1 on failure.
 */
int save_lost_items(const char *filename, LostItem *arr, int count) {
    FILE *f = fopen(filename, "wb");        // open for writing binary
    if (!f) return -1;                      // fail if cannot open
    if (fwrite(&count, sizeof(int), 1, f) != 1) { fclose(f); return -1; } // write count
    if (count > 0) {
        if (fwrite(arr, sizeof(LostItem), (size_t)count, f) != (size_t)count) {
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

/* load_lost_items:
 * Load LostItem array from filename. Allocates *out (caller must free).
 * Sets *count to the number of items loaded.
 * Returns 0 on success, -1 on read error, or 0 with *count==0 if file absent.
 */
int load_lost_items(const char *filename, LostItem **out, int *count) {
    *out = NULL; *count = 0;
    FILE *f = fopen(filename, "rb");  // open for reading binary
    if (!f) return 0;                 // no file => treat as empty DB (not an error)
    if (fread(count, sizeof(int), 1, f) != 1) { fclose(f); return -1; } // read count
    if (*count > 0) {
        *out = (LostItem*)malloc(sizeof(LostItem) * (*count)); // allocate
        if (!*out) { fclose(f); return -1; }
        if (fread(*out, sizeof(LostItem), (size_t)(*count), f) != (size_t)(*count)) {
            free(*out); *out = NULL; fclose(f); return -1;
        }
    }
    fclose(f);
    return 0;
}

/* save_found_items and load_found_items: same logic as lost versions. */

int save_found_items(const char *filename, FoundItem *arr, int count) {
    FILE *f = fopen(filename, "wb");
    if (!f) return -1;
    if (fwrite(&count, sizeof(int), 1, f) != 1) { fclose(f); return -1; }
    if (count > 0) {
        if (fwrite(arr, sizeof(FoundItem), (size_t)count, f) != (size_t)count) {
            fclose(f); return -1;
        }
    }
    fclose(f);
    return 0;
}

int load_found_items(const char *filename, FoundItem **out, int *count) {
    *out = NULL; *count = 0;
    FILE *f = fopen(filename, "rb");
    if (!f) return 0;
    if (fread(count, sizeof(int), 1, f) != 1) { fclose(f); return -1; }
    if (*count > 0) {
        *out = (FoundItem*)malloc(sizeof(FoundItem) * (*count));
        if (!*out) { fclose(f); return -1; }
        if (fread(*out, sizeof(FoundItem), (size_t)(*count), f) != (size_t)(*count)) {
            free(*out); *out = NULL; fclose(f); return -1;
        }
    }
    fclose(f);
    return 0;
}
