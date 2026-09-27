#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _POSIX_SOURCE 200809L
#define _GNU_SOURCE 
#define MAX_ENTRIES 1024
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
typedef struct {
	char path[256];
	unsigned char d_type;
} FileEntry;

#endif
