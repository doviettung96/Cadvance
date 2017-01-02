#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char getMenu(char sections[][40], int maxsection);
//create a menu
void dupChar(char c, int times);
//duplicate a character n times
void myfflush();
//scanf the space
void standardizeName(char *str);
// standardized name
char** str_split(char* a_str, const char a_delim);


