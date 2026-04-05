#include "../include/bracket.h"
#include <stdio.h>

//BRACKET CHECK (STACK)
void bracket(fileLine arr[], int len) {
    char stack[1000];
    int lineStack[1000];
    int top = -1;
    int errorFound = 0;
    
    for (int i = 0; i < len; i++) {
        int inString = 0;
        for (int j = 0; j < arr[i].lineLen; j++) {
            char ch = arr[i].lineText[j];

            // ignore bracket inside strings
            if (ch == '\"') {
                inString = !inString;
                continue;
            }
            if (inString) continue;

            if (ch == '{' || ch == '(' || ch == '[') {
                stack[++top] = ch;
                lineStack[top] = arr[i].lineNo;
            }
            else if (ch == '}' || ch == ')' || ch == ']') {
                if (top == -1) {
                    printf("Line %d: Extra '%c'\n", arr[i].lineNo, ch);
                    errorFound=1;
                } else {
                    char open = stack[top--];
                    if ((open == '{' && ch != '}') ||
                    (open == '(' && ch != ')') ||
                    (open == '[' && ch != ']')) {
                        printf("Line %d: Mismatch '%c' with '%c'\n",
                            arr[i].lineNo, open, ch);
                        errorFound=1;
                    }
                }
            }
        }
    }
    while (top != -1) {
        printf("Line %d: Unmatched '%c'\n",
            lineStack[top], stack[top]);
        top--;
        errorFound=1;
    }
    if (!errorFound) {
        printf("All brackets are balanced correctly ✅\n");
    }
}
