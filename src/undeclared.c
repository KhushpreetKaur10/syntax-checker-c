#include "../include/undeclared.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//DETECT UNDECLARED VARS
void undeclaredVariables(fileLine arr[], int len){
    char declared[200][50];
    int declCount = 0;
    char reportedGlobal[200][50];
    int globalCount = 0;
    const char *types[] = {"int","char","long","double","float","short"};
    const char *ignore[] = {
        "printf","scanf","gets","puts","return","for","while","if","else",
        "int","char","float","long","double","struct","void",
        "main","include"
    };
    int ignoreCount = 18;

    //STORE DECLARED VARIABLES
    for (int i = 0; i < len; i++) {
        char line[200];
        strcpy(line, arr[i].lineText);
        char *ptr = line;
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (strchr(ptr, '(') && strchr(ptr, ')')) continue;
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

        char *rest = strchr(ptr, ' ');
        if (!rest) continue;
        rest++;
        char vars[200];
        strcpy(vars, rest);
        char *var = strtok(vars, ",;");
        while (var != NULL) {
            while (*var == ' ' || *var == '\t') var++;
            char name[50];
            int k = 0;
            for (int j = 0; var[j] && var[j] != '=' && var[j] != '['; j++)
                name[k++] = var[j];
            name[k] = '\0';
            if (isalpha(name[0])) {
                strcpy(declared[declCount++], name);
            }
            var = strtok(NULL, ",;");
        }
    }

    //CHECK USAGE
    for (int i = 0; i < len; i++) {
        char line[200];
        strcpy(line, arr[i].lineText);
        char *token = strtok(line, " \t\n(){}[];,+-*/=<>!&|#\"");
        while (token != NULL) {
            if (!isalpha(token[0])) {
                token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|#\"");
                continue;
            }
            int skip = 0;
            for (int j = 0; j < ignoreCount; j++) {
                if (strcmp(token, ignore[j]) == 0) {
                    skip = 1;
                    break;
                }
            }
            if (strchr(token, '.')) skip = 1;
            char *pos = strstr(arr[i].lineText, token);
            if (pos && *(pos + strlen(token)) == '(')
                skip = 1;
            if (skip) {
                token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|#\"");
                continue;
            }
            int found = 0;
            for (int j = 0; j < declCount; j++) {
                if (strcmp(token, declared[j]) == 0) {
                    found = 1;
                    break;
                }
            }

            //CHECK GLOBAL DUPLICATE
            int alreadyGlobal = 0;
            for (int g = 0; g < globalCount; g++) {
                if (strcmp(reportedGlobal[g], token) == 0) {
                    alreadyGlobal = 1;
                    break;
                }
            }
            if (!found && !alreadyGlobal) {
                printf("Line %d: %s is undeclared\n", arr[i].lineNo, token);
                strcpy(reportedGlobal[globalCount++], token);
            }
            token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|#\"");
        }
    }
}