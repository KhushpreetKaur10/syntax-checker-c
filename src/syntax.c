#include "../include/syntax.h"
#include "../include/validator.h"
#include <stdio.h>
#include <string.h>


int isBalancedParentheses(char arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == '(') count++;
        else if (arr[i] == ')') count--;

        if (count < 0) return 0; // extra ')'
    }
    return count == 0;
}

int forcheck(char arr[], int size) {
    int semicolonCount = 0;
    int inSingleQuote = 0, inDoubleQuote = 0;

    for (int i = 0; i < size; i++) {
        // 🔹 Toggle quote states
        if (arr[i] == '\'' && !inDoubleQuote)
            inSingleQuote = !inSingleQuote;
        else if (arr[i] == '\"' && !inSingleQuote)
            inDoubleQuote = !inDoubleQuote;
        // 🔹 Count semicolons ONLY outside quotes
        else if (arr[i] == ';' && !inSingleQuote && !inDoubleQuote)
            semicolonCount++;
    }

    // 🔹 Conditions for valid for-loop
    if (semicolonCount != 2) return 1;
    if (inSingleQuote || inDoubleQuote) return 1;
    if (!isBalancedParentheses(arr, size)) return 1;

    return 0;
}

//WHILE LOOP CHECK
int whilecheck(char arr[], int size) {
    int inSingleQuote = 0, inDoubleQuote = 0;

    for (int i = 0; i < size; i++) {
        // 🔹 Toggle quotes
        if (arr[i] == '\'' && !inDoubleQuote)
            inSingleQuote = !inSingleQuote;
        else if (arr[i] == '\"' && !inSingleQuote)
            inDoubleQuote = !inDoubleQuote;
        // 🔹 Semicolon NOT allowed outside quotes
        else if (arr[i] == ';' && !inSingleQuote && !inDoubleQuote)
            return 1;
    }

    // 🔹 Final checks
    if (inSingleQuote || inDoubleQuote) return 1;
    if (!isBalancedParentheses(arr, size)) return 1;

    return 0;
}


//DETECT F CHECKS
typedef int (*checkFunc)(char[], int); //Define function pointer type

void fcheck(fileLine arr[], int len){
    char str[300], word[300];
    char keywords[8][10] = {
        "printf", "scanf", "gets", "puts",
        "fscanf", "fprintf", "for", "while"
    };
    // 🔹 Corresponding functions
    checkFunc functions[8] = {
        printcheck, scancheck, getscheck, putscheck,
        fscanfcheck, fprintfcheck, forcheck, whilecheck
    };

    for (int i = 0; i < len; i++){
        strcpy(str, arr[i].lineText);
        int k = 0;
        for (int j = 0; j <= arr[i].lineLen; j++){
            // 🔹 Word separator
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\t' || str[j] == '\0'){
                word[k] = '\0';
                if (k > 0){ // ignore empty words
                    // 🔹 Check against all keywords
                    for (int x = 0; x < 8; x++){
                        if (strcmp(word, keywords[x]) == 0 && strstr(str, word)){
                            int f = functions[x](str, arr[i].lineLen);
                            if (f)
                                printf("Error in Statement ---> line no: %d\n", arr[i].lineNo);
                            break; // stop after match
                        }
                    }
                }
                k = 0; // reset word
            }
            else{
                word[k++] = str[j];
            }
        }
    }
}