#include "../include/cleaner.h"
#include <string.h>

//FIND COMMENTS AND REMOVE THEM
/*      Start
          │
          ▼
        Open file for reading
          │
          ▼
        Initialize:
        - inComment = 0
        - realLine = 0
        - i = 0 (index for lines[])
          │
          ▼
        Read line from file (fgets)
          │
          ▼
        Increment realLine
          │
          ▼
        Initialize:
        - result[] = ""
        - k = 0
          │
          ▼
        For each character in line:
         ├─ If not inComment and '//' → break (ignore rest of line)
         ├─ Else if not inComment and '/*' → inComment = 1, skip next char
         ├─ Else if inComment and '* /' → inComment = 0, skip next char
         └─ Else if not inComment → result[k++] = current char
          │
          ▼
        Add null terminator to result[k]
          │
          ▼
        Check if result[] is blank (only spaces/tabs/newline)
          ├─ If yes → skip storing, read next line
          └─ If no → store in lines[i]:
               - lineNo = realLine
               - lineText = result[]
               - lineLen = strlen(result)
               - i++
          │
          ▼
        Loop until EOF
          │
          ▼
        Set *totalLen = i
          │
          ▼
        End
*/
void removeCommentsAndStore(FILE *input, fileLine lines[], int *totalLen) {
    char str[300];
    int inComment = 0;
    int realLine = 0;
    int i = 0;

    while (fgets(str, 300, input) != NULL) {
        realLine++;
        char result[300] = "";
        int k = 0;
        for (int j = 0; str[j] != '\0'; j++) {
            // // comment
            if (!inComment && str[j] == '/' && str[j+1] && str[j+1] == '/') {
                break;
            }
            // /* start
            else if (!inComment && str[j] == '/' && str[j+1] && str[j+1] == '*') {
                inComment = 1;
                j++;
            }
            // */ end
            else if (inComment && str[j] == '*' && str[j+1] && str[j+1] == '/') {
                inComment = 0;
                j++;
            }
            // normal char
            else if (!inComment) {
                result[k++] = str[j];
            }
        }
        result[k] = '\0';

        // skip blank lines
        char *check = result;
        while (*check == ' ' || *check == '\t' || *check == '\n') check++;
        if (*check == '\0') continue;

        lines[i].lineNo = realLine;
        strcpy(lines[i].lineText, result);
        lines[i].lineLen = strlen(result);
        i++;
    }
    *totalLen = i;
}

