/* utils.c
 * Helper functions used across the project:
 * - safe input reading (read_line)
 * - yes/no prompt (confirm_prompt)
 * - date validation (valid_date) using DD/MM/YYYY
 */

#include <stdio.h>    // printf, fgets
#include <string.h>   // strlen, strncpy
#include <ctype.h>    // isdigit, tolower
#include "utils.h"    // project-wide sizes and declarations

/* read_line:
 * Prompt the user (if prompt != NULL) and read a line into buf of size 'size'.
 * Uses fgets to avoid buffer overflow and strips the trailing newline.
 */
void read_line(const char *prompt, char *buf, int size) {
    if (prompt)               // if a prompt string was provided
        printf("%s", prompt); // show it to the user

    if (fgets(buf, size, stdin) == NULL) { // read up to size-1 chars
        buf[0] = '\0';       // on error/EOF make the buffer empty
        return;
    }

    size_t len = strlen(buf);        // measure what was read
    if (len > 0 && buf[len-1] == '\n') // if last char is newline
        buf[len-1] = '\0';          // remove it so strings don't end with '\n'
}

/* confirm_prompt:
 * Show a prompt expecting a yes/no answer.
 * Returns 1 for yes (y/Y), otherwise 0.
 */
int confirm_prompt(const char *prompt) {
    char buf[8];
    read_line(prompt, buf, sizeof(buf));        // reuse read_line for safety
    return (buf[0] == 'y' || buf[0] == 'Y');   // check first character
}

/* valid_date:
 * Validate date in DD/MM/YYYY format.
 * Returns 1 if valid format and basic ranges, else 0.
 */
int valid_date(const char *d) {
    if (!d) return 0;               // null pointer -> invalid
    if (strlen(d) != 10) return 0;  // must be exactly 10 characters

    // slashes must be at positions 2 and 5: DD/MM/YYYY
    if (d[2] != '/' || d[5] != '/') return 0;

    // check digits where expected
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;      // skip slashes
        if (!isdigit((unsigned char)d[i])) return 0; // non-digit -> invalid
    }

    // convert substrings to integers for range checks
    int day = (d[0]-'0')*10 + (d[1]-'0');
    int month = (d[3]-'0')*10 + (d[4]-'0');
    int year = (d[6]-'0')*1000 + (d[7]-'0')*100 + (d[8]-'0')*10 + (d[9]-'0');

    if (month < 1 || month > 12) return 0;  // basic month check
    if (day < 1 || day > 31) return 0;      // basic day check

    // improve day range for months with 30 days
    if ((month==4 || month==6 || month==9 || month==11) && day > 30) return 0;

    // February check (basic - not handling leap year fully)
    if (month == 2 && day > 29) return 0;
    if (year < 1900 || year > 2100) return 0; // reasonable year range

    return 1; // passed all checks
}
