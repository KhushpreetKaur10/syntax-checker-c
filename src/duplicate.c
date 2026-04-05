#include "../include/duplicate.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//DETECT DUPLICATE DECLARED VARS
void duplicateVariables(fileLine *arr, int len){
    const char *types[] = {"int","char","long","double","float","short"};
    char scopeVars[200][50];
    int scopeCount = 0;
    int braceCount = 0;

    for (int i = 0; i < len; i++){
        char line[200];
        strcpy(line, arr[i].lineText);
        // update scope using {}
        for (int j = 0; line[j]; j++) {
            if (line[j] == '{') {
                braceCount++;
                scopeCount = 0;   //NEW SCOPE → reset
            }
            else if (line[j] == '}') {
                braceCount--;
                scopeCount = 0;   //EXIT SCOPE → reset
            }
        }
        //ignore outside any scope
        if (braceCount <= 0) continue;
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (strlen(ptr) == 0) continue;

        // skip function headers
        if (strchr(ptr, '(') && strchr(ptr, ')') && strchr(ptr, '{') == NULL)
            continue;
        // check datatype
        char temp[200];
        strcpy(temp, ptr);
        char *token = strtok(temp, " \t;");
        int isType = 0;
        for (int t = 0; t < 6; t++) {
            if (token && strcmp(token, types[t]) == 0) {
                isType = 1;
                break;
            }
        }
        if (!isType) continue;

        // extract variables
        char *rest = strchr(ptr, ' ');
        if (!rest) continue;
        rest++;
        char vars[200];
        strcpy(vars, rest);
        char *var = strtok(vars, ",;");
        while (var != NULL){
            while (*var == ' ' || *var == '\t') var++;
            char name[50];
            int k = 0;
            for (int j = 0; var[j] && var[j] != '=' && var[j] != '['; j++)
                name[k++] = var[j];
            name[k] = '\0';
            if (!isalpha(name[0])) {
                var = strtok(NULL, ",;");
                continue;
            }
            // check duplicate in SAME SCOPE
            for (int j = 0; j < scopeCount; j++) {
                if (strcmp(scopeVars[j], name) == 0) {
                    printf("Line %d: Duplicate variable '%s'\n", arr[i].lineNo, name);
                    break;
                }
            }
            strcpy(scopeVars[scopeCount++], name);
            var = strtok(NULL, ",;");
        }
    }
}