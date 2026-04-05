#include "../include/function.h"
#include <stdio.h>
#include <string.h>

// COUNT FUNCTIONS AND PROTOTYPES
void function_and_prototype_count(fileLine arr[], int len)
{
    const char *types[] = {"int", "char", "void", "double", "float", "long", "short"};
    int totalFunctions = 0;
    int totalPrototypes = 0;
    int mainLine = -1;

    // find main line
    for (int i = 0; i < len; i++) {
        if (strstr(arr[i].lineText, "main(")) {
            mainLine = i;
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        char line[200];
        strcpy(line, arr[i].lineText);

        // remove leading spaces
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        if (strlen(ptr) == 0) continue;

        // must contain ()
        if (!(strchr(ptr, '(') && strchr(ptr, ')')))
            continue;

        // ignore control statements
        if (strstr(ptr, "for(") || strstr(ptr, "while(") ||
            strstr(ptr, "if(") || strstr(ptr, "switch("))
            continue;

        // extract first word
        char temp[200];
        strcpy(temp, ptr);
        char *token = strtok(temp, " \t(");

        int isType = 0;
        for (int t = 0; t < 7; t++) {
            if (token && strcmp(token, types[t]) == 0) {
                isType = 1;
                break;
            }
        }

        if (!isType) continue;

        // prototype
        // check if line ends with ';' (ignore spaces)
        int k = strlen(ptr) - 1;
        while (k >= 0 && (ptr[k] == ' ' || ptr[k] == '\t' || ptr[k] == '\n'))
            k--;
            
        if (k >= 0 && ptr[k] == ';') {
            if (i < mainLine)
                totalPrototypes++;
        }
        else {
            totalFunctions++;
        }
    }

    printf("Total Functions used including main: %d\n", totalFunctions);
    printf("Total Prototypes before main: %d\n", totalPrototypes);

    if (totalPrototypes < totalFunctions - 1)
        printf("Some prototypes are not defined\n");
    else
        printf("Prototypes are defined\n");
}