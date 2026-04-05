#include "../include/builtin.h"
#include <stdio.h>
#include <string.h>

//DETECT BUILTIN FNS
void builtinfunction(fileLine arr[], int len) {
    char sync[30][20] = {
        "printf", "scanf", "gets", "puts", "fscanf", "fprintf", "fgets", "fputs", "fputc", "fgetc", "fopen", "fclose", "feof", "fflush", "malloc", "calloc", "rand", "strcmp", "strlen", "strcpy", "strncpy", "strncmp", "tolower", "toupper", "strrev", "getch", "strcat", "strncat", "sqrt","pow"
    };

    int count[30] = {0}; // store count for each function
    int total = 0;

    for (int i = 0; i < len; i++) {
        char lineCopy[200];
        strcpy(lineCopy, arr[i].lineText);

        //remove detection inside strings
        int inString = 0;
        char cleaned[200];
        int k = 0;
        for (int j = 0; lineCopy[j] != '\0'; j++) {
            if (lineCopy[j] == '\"') {
                inString = !inString; // toggle
                continue;             // skip quotes
            }
            if (!inString) {
                cleaned[k++] = lineCopy[j];
            }
        }
        cleaned[k] = '\0';

        const char *delim = " \t();,\n"; // delimiters
        char *token = strtok(cleaned, delim);

        while (token != NULL) {
            for (int j = 0; j < 30; j++) {
                if (strcmp(token, sync[j]) == 0) {
                    count[j]++;
                    total++;
                    break; // stop checking once matched
                }
            }
            token = strtok(NULL, delim);
        }
    }

    // Print individual counts
    printf("Built-in Function Counts:\n");
    for (int j = 0; j < 30; j++) {
        if (count[j] > 0) {
            printf("%s: %d\n", sync[j], count[j]);
        }
    }

    printf("Total Builtin Functions: %d\n", total);
}