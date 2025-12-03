/* report.c
 * Generates a simple daily_report.txt summarizing counts and listing recent items.
 */

#include <stdio.h>
#include <stdlib.h>
#include "report.h"
#include "fileops.h"
#include "lost.h"
#include "found.h"

/* generate_daily_report:
 * Reads lost and found DBs and writes a simple textual summary to out_file.
 * Returns 0 on success, -1 on error.
 */
int generate_daily_report(const char *lost_file, const char *found_file, const char *out_file) {
    LostItem *lost = NULL; int ln = 0;
    FoundItem *found = NULL; int fn = 0;
    if (load_lost_items(lost_file, &lost, &ln) < 0) return -1;
    if (load_found_items(found_file, &found, &fn) < 0) { if (lost) free(lost); return -1; }

    FILE *f = fopen(out_file, "w"); // write plain text report
    if (!f) { free(lost); free(found); return -1; }
    fprintf(f, "Lost & Found Daily Report\n");
    fprintf(f, "=========================\n\n");
    fprintf(f, "Total lost items: %d\n", ln);
    fprintf(f, "Total found items: %d\n\n", fn);

    fprintf(f, "Recent Lost Items:\n");
    for (int i = 0; i < ln; ++i) {
        fprintf(f, "ID:%d Reporter:%s Category:%s Date:%s Location:%s\n  Desc: %s\n",
                lost[i].id, lost[i].name, lost[i].category, lost[i].date, lost[i].location, lost[i].description);
    }

    fprintf(f, "\nRecent Found Items:\n");
    for (int i = 0; i < fn; ++i) {
        fprintf(f, "ID:%d Finder:%s Category:%s Date:%s Location:%s\n  Desc: %s\n",
                found[i].id, found[i].name, found[i].category, found[i].date, found[i].location, found[i].description);
    }

    fclose(f);
    free(lost);
    free(found);
    return 0;
}
