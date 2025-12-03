#ifndef UTILS_H
#define UTILS_H

#define NAME_LEN 50
#define CAT_LEN 30
#define LOC_LEN 60
#define DATE_LEN 12
#define DESC_LEN 200

void read_line(const char *prompt, char *buf, int size);
int confirm_prompt(const char *prompt);
int valid_date(const char *d);

#endif
