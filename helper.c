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
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

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
		if (content->d_name[0] == '.')
			continue;

		//store full file path from current directory
		char temp[1024] = {0};

		// make full path
		makepath(temp, dir, content->d_name);
	
		// recall itself if another directory found
		if (isdir(temp))
		{
			// read this new directory found
			getFiles(files, temp);
			continue; // don't include directories in list
		}

		// allocate memory to store locations of char *
		*files = realloc(*files, (i + 2) * (sizeof(char *)));

		// allocate heap memory and store location
		(*files)[i] = (char *)strdup(temp);
		// move to next location
		i++;
	}
	
	// free directory handler
	closedir(dd);

	// set NULL after last file name
	(*files)[i] = '\0';
}


/*
 * returns true if 'dir' refers to a directory, false otherwise
 */
bool isdir(const char * dir)
{
	int fd = open(dir, O_RDONLY | O_NONBLOCK);

	// stores file info
	struct stat buf;

	// get file info
	if (fstat(fd, &buf) < 0)
		return false; // for files whose stats can't be get mostly due to no permissions.

	// close the fd as we got stats by now
	close(fd);

	if (S_ISDIR(buf.st_mode)) 
		return true;
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
