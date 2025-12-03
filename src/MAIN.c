/* main.c
 * Entry point and menu for the Lost & Found Management System.
 * Handles user interaction and calls module functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lost.h"
#include "found.h"
#include "match.h"
#include "report.h"
#include "utils.h"

#define LOST_DB "lost.db"       // file names used in the project
#define FOUND_DB "found.db"
#define REPORT_FILE "daily_report.txt"

/* show_menu: print the user menu */
void show_menu(void) {
    printf("=== Lost & Found Management ===\n");
    printf("1. Add lost item\n");
    printf("2. Add found item\n");
    printf("3. List lost items\n");
    printf("4. List found items\n");
    printf("5. Search lost items\n");
    printf("6. Search found items\n");
    printf("7. Match lost & found\n");
    printf("8. Generate daily report\n");
    printf("9. Exit\n");
}

/* main: interactive loop reading options and executing them */
int main(void) {
    while (1) {
        show_menu();
        char buf[8];
        read_line("Choose option: ", buf, sizeof(buf)); // safe input for option
        int opt = atoi(buf); // convert to integer (0 if invalid)

        if (opt == 1) {
            LostItem it = {0}; // zero-initialize struct
            read_line("Your name: ", it.name, sizeof(it.name));
            read_line("Category: ", it.category, sizeof(it.category));
            read_line("Location lost: ", it.location, sizeof(it.location));
            // loop until a valid date is provided
            while (1) {
                read_line("Date (DD/MM/YYYY): ", it.date, sizeof(it.date));
                if (valid_date(it.date)) break;
                printf("Invalid date format. Please use DD/MM/YYYY.\n");
            }
            read_line("Description: ", it.description, sizeof(it.description));
            if (add_lost_item(&it, LOST_DB) == 0) printf("Added lost item successfully.\n");
            else printf("Error adding lost item.\n");

        } else if (opt == 2) {
            FoundItem it = {0};
            read_line("Finder name (type 'unknown' if not known): ", it.name, sizeof(it.name));
            read_line("Category: ", it.category, sizeof(it.category));
            read_line("Location found: ", it.location, sizeof(it.location));
            while (1) {
                read_line("Date (DD/MM/YYYY): ", it.date, sizeof(it.date));
                if (valid_date(it.date)) break;
                printf("Invalid date format. Please use DD/MM/YYYY.\n");
            }
            read_line("Description: ", it.description, sizeof(it.description));
            if (add_found_item(&it, FOUND_DB) == 0) printf("Added found item successfully.\n");
            else printf("Error adding found item.\n");

        } else if (opt == 3) {
            list_lost_items(LOST_DB);

        } else if (opt == 4) {
            list_found_items(FOUND_DB);

        } else if (opt == 5) {
            char kw[80];
            read_line("Enter keyword to search lost items: ", kw, sizeof(kw));
            search_lost_items(LOST_DB, kw);

        } else if (opt == 6) {
            char kw[80];
            read_line("Enter keyword to search found items: ", kw, sizeof(kw));
            search_found_items(FOUND_DB, kw);

        } else if (opt == 7) {
            match_lost_and_found(LOST_DB, FOUND_DB);

        } else if (opt == 8) {
            if (generate_daily_report(LOST_DB, FOUND_DB, REPORT_FILE) == 0)
                printf("Report generated: %s\n", REPORT_FILE);
            else
                printf("Error generating report.\n");

        } else if (opt == 9) {
            printf("Exiting. Goodbye.\n");
            break;

        } else {
            printf("Invalid option. Please choose 1-9.\n");
        }

        printf("\n"); // blank line before printing menu again
    }

    return 0;
}
