#include "../include/validator.h"
#include "../include/parser.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//DETECTS PRINTF
int printcheck(char arr[], int size){
    char format[200];
    if (!extractFormat(arr, format)) return 1;

    char specs[20][5];
    int specCount;
    extractSpecifiers(format, specs, &specCount);

    char vars[20][50];
    int varCount;
    extractVariables(arr, vars, &varCount);

    if (specCount != varCount) return 1;

    // printf should NOT have &
    for (int i = 0; i < varCount; i++){
        if (vars[i][0] == '&')
            return 1;
    }

    return 0;
}

//DETECTS SCANF
int scancheck(char arr[], int size){
    char format[200];
    if (!extractFormat(arr, format)) return 1;

    char specs[20][5];
    int specCount;
    extractSpecifiers(format, specs, &specCount);

    char vars[20][50];
    int varCount;
    extractVariables(arr, vars, &varCount);

    if (specCount != varCount) return 1;

    for (int i = 0; i < specCount; i++){
        // %s should NOT have &
        if (strcmp(specs[i], "%s") == 0 && vars[i][0] == '&')
            return 1;
        // others MUST have &
        if (strcmp(specs[i], "%s") != 0 && vars[i][0] != '&')
            return 1;
    }

    return 0;
}

//DETECTS FPRINTF
int fprintfcheck(char arr[], int size){
    return printcheck(arr, size);  // same logic
}

//DETECTS FSCANF
int fscanfcheck(char arr[], int size){
    return scancheck(arr, size);  // same logic
}

// GETS AND PUTS
int getscheck(char arr[], int size){
    char *p = strchr(arr, '(');
    if (!p) return 1;

    p++;
    while (*p == ' ' || *p == '\t') p++;

    // ❌ string literal
    if (*p == '\"') return 1;

    // extract variable
    char var[50];
    int k = 0;

    while (*p && *p != ')' && *p != ';')
        var[k++] = *p++;

    var[k] = '\0';

    // trim
    trim(var);

    // ❌ must be valid identifier (char array expected)
    if (!isalpha(var[0])) return 1;
    // ❌ reject single letter variables (likely int)
    if (strlen(var) == 1)
        return 1;

    return 0;
}

int putscheck(char arr[], int size){
    char *p = strchr(arr, '(');
    if (!p) return 1;

    p++;
    while (*p == ' ' || *p == '\t') p++;

    // puts can accept string literal OR variable
    if (*p == '\0') return 1;

    return 0;
}



// MAIN DRIVER
//DETECTS PRINTF SCANF
void printscan(fileLine arr[], int size){
    for (int i = 0; i < size; i++){
        char *line = arr[i].lineText;

        if (strstr(line, "printf")){
            if (printcheck(line, arr[i].lineLen))
                printf("printf ERROR\n");
            else
                printf("printf OK\n");
        }

        if (strstr(line, "scanf")){
            if (scancheck(line, arr[i].lineLen))
                printf("scanf ERROR\n");
            else
                printf("scanf OK\n");
        }

        if (strstr(line, "fprintf")){
            if (fprintfcheck(line, arr[i].lineLen))
                printf("fprintf ERROR\n");
            else
                printf("fprintf OK\n");
        }

        if (strstr(line, "fscanf")){
            if (fscanfcheck(line, arr[i].lineLen))
                printf("fscanf ERROR\n");
            else
                printf("fscanf OK\n");
        }

        if (strstr(line, "gets")){
            if (getscheck(line, arr[i].lineLen))
                printf("gets ERROR\n");
            else
                printf("gets OK\n");
        }

        if (strstr(line, "puts")){
            if (putscheck(line, arr[i].lineLen))
                printf("puts ERROR\n");
            else
                printf("puts OK\n");
        }
    }
}
