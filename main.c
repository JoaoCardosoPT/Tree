#define _POSIX_SOURCE 200809L
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void openfile(char *fn, int indent)
{
	DIR *dir;	
	struct dirent *entry;
	int count;
	char path[1025];
	struct stat info;
	int len;
	
	// How many identations spaces
	for (count = 0; count < indent; count++)
		printf("  ");
	printf("%s\n", fn);
	
	if ((dir = opendir(fn)) == NULL)
		perror("Error Openening Directory");
	else
	{
		while((entry = readdir(dir)) != NULL)
		{
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			// avoid overflow
			len = snprintf(path, sizeof(path), "%s/%s", fn, entry->d_name);
			if (len < 0 || len >= (int)sizeof(path))
			{
				fprintf(stderr, "Path to long");
				continue;
			}
			if (stat(path, &info) != 0)
				fprintf(stderr, "error in %s: %s\n", path, strerror(errno));
			// checks if its a directory
			else if (S_ISDIR(info.st_mode))
				openfile(path, indent+1);
		}
		closedir(dir);
	}
		
}

int main(void)
{
	openfile("../treeinC/", 0);
}
