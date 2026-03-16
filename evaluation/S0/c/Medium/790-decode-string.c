// Source: https://leetcode.com/problems/decode-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an encoded string, return its decoded string.
//
// The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
//
// You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
//
// The test cases are generated so that the length of the output will never exceed 105.
//
// Example:
// Input: s = "3[a]2[bc]"
// Output: "aaabcbc"
//
// Constraints:
// 1 <= s.length <= 30
// 	s consists of lowercase English letters, digits, and square brackets '[]'.
// 	s is guaranteed to be a valid input.
// 	All the integers in s are in the range [1, 300].
//

char* decodeString(char* s) {
    int n = strlen(s);
    char* stack[n];
    int top = -1;
    int i = 0;

    while (i < n) {
        if (s[i] != ']') {
            char* str = (char*)malloc(2 * sizeof(char));
            str[0] = s[i];
            str[1] = '\0';
            stack[++top] = str;
            i++;
        } else {
            char* substr = (char*)malloc(1 * sizeof(char));
            substr[0] = '\0';
            while (top >= 0 && stack[top][0] != '[') {
                char* temp = (char*)malloc((strlen(stack[top]) + strlen(substr) + 1) * sizeof(char));
                strcpy(temp, stack[top]);
                strcat(temp, substr);
                free(substr);
                substr = temp;
                free(stack[top--]);
            }
            free(stack[top--]); // pop '['

            char* numStr = (char*)malloc(1 * sizeof(char));
            numStr[0] = '\0';
            while (top >= 0 && isdigit(stack[top][0])) {
                char* temp = (char*)malloc((strlen(stack[top]) + strlen(numStr) + 1) * sizeof(char));
                strcpy(temp, stack[top]);
                strcat(temp, numStr);
                free(numStr);
                numStr = temp;
                free(stack[top--]);
            }
            int repeatCount = atoi(numStr);
            free(numStr);

            char* expandedStr = (char*)malloc((strlen(substr) * repeatCount + 1) * sizeof(char));
            expandedStr[0] = '\0';
            for (int j = 0; j < repeatCount; j++) {
                strcat(expandedStr, substr);
            }
            free(substr);
            stack[++top] = expandedStr;
            i++;
        }
    }

    char* result = (char*)malloc(1 * sizeof(char));
    result[0] = '\0';
    while (top >= 0) {
        char* temp = (char*)malloc((strlen(stack[top]) + strlen(result) + 1) * sizeof(char));
        strcpy(temp, stack[top]);
        strcat(temp, result);
        free(result);
        result = temp;
        free(stack[top--]);
    }

    return result;      
}
