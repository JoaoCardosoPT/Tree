#include "include/functions.h"
#include <dirent.h>
#include <string.h>

int compare_string(const void *a, const void *b)
{
	FileEntry *entryA = (FileEntry *)a;
	FileEntry *entryB = (FileEntry *)b;
	return strcmp(entryA->path, entryB->path);
}

void openfile(char *fn, int indent)
{
	DIR *dir;	
	int count;
	struct stat info;
	struct dirent *raw_entry;
	
	FileEntry *entries = malloc(MAX_ENTRIES * sizeof(FileEntry));

	// How many identations spaces
	for (count = 0; count < indent; count++)
		printf("  ");
	printf(".\n");	
	if ((dir = opendir(fn)) == NULL)
		perror("Error Openening Directory");
	else
	{
		while ((raw_entry = readdir(dir)) != NULL && count < MAX_ENTRIES)
		{
			if (strcmp(raw_entry->d_name, ".") == 0 || strcmp(raw_entry->d_name, "..") == 0)
				continue;
			strncpy(entries[count].path, raw_entry->d_name, 255);
			entries[count].d_type = raw_entry->d_type;
			count++;
		}
		qsort(entries, count, sizeof(FileEntry), compare_string);

		// files and dirs 
		for (int i = 0; i < count; i++)
		{
			if (i == count - 1)
				printf("└──");
			else	
				printf("├── ");
			if (entries[i].d_type == DT_DIR)
				printf("%s\n", entries[i].path);
			else	
				printf("%s\n", entries[i].path);
		}
	}
	closedir(dir);
	free(entries);
}

int main(void)
{
	openfile("..", 0);
}
