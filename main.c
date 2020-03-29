#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#define MAX_BUFFER 255

enum Error { NoFileGiven=69, NoFileError=420, RegexNotCompiled=1337, RegexErrorUndifined=42069};

int check_if_file(int arguments){
    if (arguments < 3){
        printf("No file given");
        exit(NoFileGiven);
    }
    return 0;
}

FILE * check_if_file_exist(char * filename){
    FILE * file;
    file = fopen(filename, "r");
    if (file == NULL){
        printf("Could not find file %s", filename);
        exit(NoFileError);
    }
    return file;
}

regex_t create_regex(char * expression ){
    regex_t regex;
    int error = regcomp(&regex, expression, 0);
    if (error){
        printf("Could not process regex");
        exit(RegexNotCompiled);
    }
    return regex;
}

void read_file(FILE * file, regex_t regex){
    char buffer[MAX_BUFFER];
    int line = 0;
    while (fgets(buffer, MAX_BUFFER, file) != NULL){
        line++;
        int error = regexec(&regex, buffer, 0, NULL, 0);
        if(!error){
            printf("%d| %s", line, buffer);
        } else if (error == REG_NOMATCH){
            continue;
        } else{
            char errorType[100];
            regerror(error, &regex, errorType, sizeof(errorType));
            fprintf(stderr, "Regex match failed: %s\n", errorType);
        }
    }
}

int main(int argc, char **argv){
    check_if_file(argc);
    FILE * file = check_if_file_exist(argv[2]);
    regex_t regex = create_regex(argv[1]);
    read_file(file, regex);
}