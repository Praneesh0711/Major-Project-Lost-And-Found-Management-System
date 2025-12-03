#ifndef LOST_H
#define LOST_H

#include "utils.h"

typedef struct {
    int id;
    char name[NAME_LEN];
    char category[CAT_LEN];
    char location[LOC_LEN];
    char date[DATE_LEN];
    char description[DESC_LEN];
} LostItem;

int add_lost_item(const LostItem *it, const char *filename);
int list_lost_items(const char *filename);
int search_lost_items(const char *filename, const char *keyword);

#endif
