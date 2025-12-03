#ifndef FILEOPS_H
#define FILEOPS_H

#include "lost.h"
#include "found.h"

int save_lost_items(const char *filename, LostItem *arr, int count);
int load_lost_items(const char *filename, LostItem **out, int *count);

int save_found_items(const char *filename, FoundItem *arr, int count);
int load_found_items(const char *filename, FoundItem **out, int *count);

#endif
