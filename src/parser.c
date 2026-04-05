#include "../include/parser.h"
#include <string.h>
#include <ctype.h>


//DETECT SPECIFIERS
void extractSpecifiers(char format[], char specs[][5], int *count){
    *count = 0;
    for (int i = 0; format[i]; i++){ //Equivalent to: while(format[i] != '\0')
        if (format[i] == '%' && format[i+1]){
            int k = 0;
            specs[*count][k++] = '%';
            i++;
            // handle %lf
            if (format[i] == 'l' && format[i+1] == 'f'){
                specs[*count][k++] = 'l';
                specs[*count][k++] = 'f';
                i++;
            }
            else{
                specs[*count][k++] = format[i];
            }
            specs[*count][k] = '\0';
            (*count)++;
        }
    }
}

//DETECT FORMATS...find string i.e. whatever inside ""
int extractFormat(char arr[], char format[]){
    int i = 0, k = 0;
    while (arr[i] && arr[i] != '\"') i++;
    if (!arr[i]) return 0;
    i++;

    while (arr[i] && arr[i] != '\"')
        format[k++] = arr[i++];

    format[k] = '\0';
    if (!arr[i]) return 0;
    return 1;
}

//TRIM SPACES
void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    // remove leading spaces
    while (isspace(str[start])) start++;
    // remove trailing spaces and symbols
    while (end >= start && (isspace(str[end]) || str[end] == ')' || str[end] == ';'))
        end--;
    int k = 0;
    for (int i = start; i <= end; i++)
        str[k++] = str[i];
    str[k] = '\0';
}

//DETECT ARGUMENT VARIABLE NAMES
void extractVariables(char arr[], char vars[][50], int *count) {
    *count = 0;
    int i = 0;
    // 🔹 Step 1: Skip till first quote
    while (arr[i] && arr[i] != '\"') i++;
    if (!arr[i]) return;
    i++;
    // 🔹 Step 2: Skip format string
    while (arr[i] && arr[i] != '\"') i++;
    if (!arr[i]) return;
    i++;

    char temp[200];
    int k = 0;

    int parenDepth = 0; // 🔥 key improvement
    // 🔹 Step 3: Parse arguments
    while (arr[i]) {
        if (arr[i] == '(') parenDepth++;
        if (arr[i] == ')') parenDepth--;
        // split only when comma is OUTSIDE parentheses
        if (arr[i] == ',' && parenDepth == 0) {
            temp[k] = '\0';
            trim(temp);
            if (strlen(temp) > 0) {
                strcpy(vars[*count], temp);
                (*count)++;
            }
            k = 0;
        }
        else {
            temp[k++] = arr[i];
        }
        i++;
    }
    // 🔹 Last argument
    temp[k] = '\0';
    trim(temp);

    if (strlen(temp) > 0) {
        strcpy(vars[*count], temp);
        (*count)++;
    }
}