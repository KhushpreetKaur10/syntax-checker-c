#include "../include/keyword.h"
#include <string.h>
#include <stdio.h>

//FIND KEYWORDS
void keyword(fileLine arr[], int len) {
    //const → ensures keywords cannot be modified
    //👉 Why pointer (char *)? Because strings are stored as addresses, not full arrays.
    const char *keywords[] = {
        "auto","double","int","struct","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","signed","void","default","goto","sizeof","volatile","do","if","static","while"
    };
    // int totalKeywords = 32;
    int totalKeywords = sizeof(keywords) / sizeof(keywords[0]); //This works only when array is NOT passed as pointer as an argument to function

    for (int i = 0; i < len; i++) {
        char temp[300];
        strcpy(temp, arr[i].lineText);

        //remove strings
        int inString = 0;
        char cleaned[300];
        int k = 0;

        for (int j = 0; temp[j] != '\0'; j++) {
            if (temp[j] == '\"') {
                inString = !inString; // toggle
                continue;             // skip quotes
            }
            if (!inString) {
                cleaned[k++] = temp[j];
            }
        }
        cleaned[k] = '\0';

        char *token = strtok(cleaned, " \t\n(){}[];,+-*/=<>!&|");

        while (token != NULL) {
            for (int j = 0; j < totalKeywords; j++) {
                if (strcmp(token, keywords[j]) == 0) {
                    printf("Line %d: %s\n", arr[i].lineNo, token);
                }
            }
            token = strtok(NULL, " \t\n(){}[];,+-*/=<>!&|");
        }
    }
}