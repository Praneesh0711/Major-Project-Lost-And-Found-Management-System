#ifndef FOUND_H
#define FOUND_H

#include "utils.h"

typedef struct {
    int id;
    char name[NAME_LEN];
    char category[CAT_LEN];
    char location[LOC_LEN];
    char date[DATE_LEN];
    char description[DESC_LEN];
} FoundItem;

/* Function prototypes - must match exactly the function names in found.c */
int add_found_item(const FoundItem *it, const char *filename);
int list_found_items(const char *filename);
int search_found_items(const char *filename, const char *keyword);

#endif
