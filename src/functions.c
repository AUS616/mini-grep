#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 1024
#define RED "\033[31m"
#define RESET "\033[0m"

void help_command(){
    printf("Usage: ./minigrep <pattern> <file> \n");
    printf("search for pattern in each file \n");
    printf("example: ./minigrep 'hello' sample.txt \n");
    printf("Options:\n");
    printf("  -i, --invert-match: Invert the sense of matching\n");
    printf("  -c, --count: Print only a count of matching lines per file\n");
    printf("  -ci --case-insensitive: Perform case insensitive matching\n");
    
    


}

void search_pattern(FILE *fp, const char* pattern){
    
    char line[MAX];
    int line_number = 1;
    int found = 0;

    rewind(fp);

    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);

        
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

    
        if (strstr(line, pattern)) {
            found = 1;
            char *pos = line;
            char *match;

            
            printf("Line %d: ", line_number);

            
            while ((match = strstr(pos, pattern)) != NULL) {
                
                printf("%.*s", (int)(match - pos), pos);

                
                printf(RED "%.*s" RESET, (int)strlen(pattern), match);

                
                pos = match + strlen(pattern);
            }
            
            printf("%s\n", pos);
        }

        line_number++;
    }

    if (!found) {
        printf("'%s' not found in the file.\n", pattern);
    }
}

void invert_match(FILE *fp, const char* pattern){
    
    char line[MAX];
    int line_number = 1;
    

    rewind(fp);  

    while(fgets(line, sizeof(line), fp)){
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        if (!strstr(line, pattern)){
            printf("Line %d: %s \n",line_number, line);
            
        }
        line_number++;  
    }
    
}


void count_match(FILE *fp,const char* pattern){
    char line[MAX];
    int line_number = 1;
    int ct=0;

    rewind(fp);  

    while(fgets(line, sizeof(line), fp)){
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        if (strstr(line, pattern)){
            ct+=1;
            
        }
        line_number++;  
    }
    printf(RED "Total matches: %d\n" RESET, ct);
}

//function to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void case_insensitive_search(FILE *fp, const char* pattern){
    
    char line[MAX];
    int line_number = 1;
    int found = 0;

    rewind(fp);
    char pattern_lower[MAX];
    strcpy(pattern_lower, pattern);
    to_lowercase(pattern_lower);

    while (fgets(line, sizeof(line), fp)) {
        size_t len = strlen(line);

        
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        char line_lower[MAX];
        strcpy(line_lower, line);
        to_lowercase(line_lower);

        
        if (strstr(line_lower, pattern_lower)) {
            found = 1;
            char *pos = line_lower;
            char *match;

            
            printf("Line %d: ", line_number);

            
            while ((match = strstr(pos, pattern_lower)) != NULL) {
                
                printf("%.*s", (int)(match - pos), line + (pos - line_lower));
                printf(RED "%.*s" RESET, (int)strlen(pattern), line + (match - line_lower));
                pos = match + strlen(pattern);
            }

            
            printf("%s\n", line + (pos - line_lower));
        }

        line_number++;
    }

    if (!found) {
        printf("'%s' not found in the file.\n", pattern);
    }
}




