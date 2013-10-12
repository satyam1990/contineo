/***************************************************************************
 *
 * helper.c
 *
 * Author: mSatyam
 *
 * 2013, October
 *
 * Implements helper functions declared in helper.h
 *
 * *************************************************************************/

#include "helper.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

/*
 * Stores the list of files present in direectory pointed by 'dir' 
 * in array of strings pointed by 'files'
 */
void getFiles(char ***files, const char* dir)
{
	static int i;

	// ensure directory is valid
	if (dir == NULL)
	{
		printf("Error: Invalid Directory\n\n");
		exit(1);
	}

	// declare and initialize directory handler
	DIR *dd = opendir(dir);
	if (dd == NULL)
	{
		printf("Error: Directory Not Found\n\n");
		exit(2);
	}

	// structure that store file attributes read
	struct dirent *content;

	// read directory until all files are scanned
	while ((content = readdir(dd)) != NULL)
	{
		// ignore '.' and '..' directories
		if (strcmp(content->d_name, ".") == 0 || 
			strcmp(content->d_name, "..") == 0)
			continue;
		/*if (content->d_name[0] == '.')
			continue;*/

		//store full file path from current directory
		char temp[1024] = {0};

		// make full path
		makepath(temp, dir, content->d_name);

		// recall itself if another directory found
		if (isdir(temp))
		{
			// read this new directory found
			getFiles(files, temp);
			continue;
		}

		// allocate memory to store locations of char *
		*files = realloc(*files, (i + 2)*(sizeof(char *)));

		// allocate heap memory and store location
		*(*(files + 0) + i) = (char *)strdup(temp);

		// move to next location
		i++;
	}
	
	// free directory handler
	closedir(dd);

	// set NULL after last file name
	*(*(files + 0) + i) = '\0';
}


/*
 * returns true if 'dir' refers to a directory, false otherwise
 */
bool isdir(const char * dir)
{
	DIR *temp;
	temp = opendir(dir);
	
	if (temp != NULL)
	{
		closedir(temp);
		return true;
	}

return false;
}


/*
 * appends dir and file/directory name to src, 
 * thus makes a full file/directory path, from current directory
 */
void makepath(char src[], const char *dir, const char *file)
{	
	// prepend directory name
	strcat(src, dir);
	strcat(src, "/");

	// append file/directory name
	strcat(src, file);
}
