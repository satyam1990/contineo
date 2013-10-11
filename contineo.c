/***************************************************************************
 * 
 * contineo.c
 *
 * Author: mSatyam
 *
 * 2013, October
 *
 * Implements contineo, which gets all files in the specified directory.
 *
 * Usage: bin/contineo [#]
 *
 * where '#' represents the name of the directory
 *
 * *************************************************************************/

#include "helper.h"

/*
 * Display's content of String array passed to it,
 * that should conatin full path to files.
 */
void display(char **);

/*
 * Free's the memory utilized by the program
 */
void cleanup(char **);

int main(int argc, char *argv[])
{
	// ensure proper usage
	if (argc != 2)
	{
		printf("Usage: %s [dir]\n\n", argv[0]);
		return 1;
	}

	char *files[1024] = {0};
	// get files from the directory specified
	getFiles(files, argv[1]);
	
	// display files
	display(files);

	// free memory utilized by files array
	cleanup(files);

// that's all folks
return 0;
}


/*
 * Display's content of String array passed to it,
 * that should conatin full path to files.
 */
void display(char *files[])
{
	// Color Red
	printf("[0;31;40m");

	// display files
	for (int i = 0; files[i]; i++)
	{
		printf("%s\n", files[i]);
	}

	// turn off color
	printf("[0;37;40m");
}


/*
 * Free's the memory utilized by the program
 */
void cleanup(char *files[])
{
	// free memory utilized by files array
	for (int i = 0; files[i]; i++)
		free(files[i]);
}
