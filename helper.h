/***************************************************************************
 *
 * helper.h
 *
 * Author: mSatyam
 *
 * 2013, October
 *
 * Prototype of helper functions required for other C files
 *
 ***************************************************************************/

#ifndef HELPER_H
#define HELPER_H

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Stores the list of files present in direectory pointed by 'dir' 
 * in array of strings pointed by 'files'
 */
void getFiles(char **, const char*);


/*
 * returns true if argument passed is a directory, false otherwise
 */
bool isdir(const char *);

/*
 * appends dir and file/directory name to src, 
 * thus makes a full file/directory path, from current directory
 */
void makepath(char src[], const char *dir, const char *file);
#endif //HELPER_H
