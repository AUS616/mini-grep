#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string.h>
#include <stdio.h>
#define RED "\033[31m"
#define RESET "\033[0m"
void help_command();
void invert_match(FILE *fp,const char* pattern);
void count_match(FILE *fp,const char* pattern);
void search_pattern(FILE *fp, const char* pattern);
void case_insensitive_search(FILE *fp, const char* pattern);


#endif