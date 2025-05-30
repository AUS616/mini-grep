#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc,char* argv[]){
    int invert_matches = 0; // -i
    int count_matches = 0; // -c
    int case_insensitive = 0; // -ci
    const char *pattern = NULL;
    const char *filename = NULL;
    

    for(int i=1;i<argc;i++){
        if (strcmp(argv[i],"--help")==0){
            help_command();
            return 0;

        }else if (strcmp(argv[i],"-i")==0){
            invert_matches = 1;

        }else if (strcmp(argv[i],"-c")==0){
            count_matches = 1;
        }else if (strcmp(argv[i],"-ci")==0){
            case_insensitive = 1;

        }
        
        else if (!pattern) {
            pattern = argv[i];
        } else if (!filename) {
            filename = argv[i];
        }
        else{
            printf("Unknown options \n");
            printf("Use --help to see the usage \n");
            return 1;
        }
    }

    if (!pattern || !filename) {
        printf("Error: Pattern and file must be specified.\n");
        printf("Use --help to see the usage \n");
        return 1;
    }

    FILE *fp = fopen(filename,"r");
    if(!fp){
        printf("Error opening the file \n");
        return 1;
    }
    
    if(invert_matches){
        invert_match(fp, pattern);
        rewind(fp);
    }else if(count_matches) {
        count_match(fp, pattern);
        rewind(fp);
    }else if(case_insensitive){
        case_insensitive_search(fp, pattern);
        rewind(fp);
    }else{
        search_pattern(fp, pattern);
        rewind(fp);
    }
    
    
    fclose(fp);
    return 0;
}