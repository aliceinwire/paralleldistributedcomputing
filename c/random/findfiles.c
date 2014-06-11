#include <stdio.h>
#include <dirent.h>

#define MIN_ARGS 2

DIR *check_path(const char *dir_path)
{
	DIR *dir = opendir(dir_path);

	if (!dir)
		perror("Can't open specified directory");
	return dir;
}

void find_files(DIR *dir)
{
	struct dirent *dentry = NULL;
	DIR *childdir = NULL;

	if (!dir)
		return;
	while (dentry = readdir(dir)) {
		if (!strcmp(dentry->d_name, ".") || 
			!strcmp(dentry->d_name, ".."))
			continue;
		printf("%s", dentry->d_name);
		if (dentry->d_type == DT_DIR) {
			childdir = opendir(dentry->d_name);
			if (childdir)
				find_files(childdir);
			else
				perror("error while recursing:");
			printf("*\n");
		} else
			printf("\n"); 
	}
	closedir(dir);
}

int main(int argc, char **argv)
{
	int retval = 0;
	DIR *dirp = NULL;

	if (argc < MIN_ARGS) {
		printf("Path to search in, is required\n");
		retval = -1;
		goto EXIT;
	}
	dirp = check_path(argv[1]);
	if (!dirp) {
		retval = -1; 
		goto EXIT;
	}
	find_files(dirp);
	EXIT:
	return retval;
}

