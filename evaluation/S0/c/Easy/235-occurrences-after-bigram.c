// Source: https://leetcode.com/problems/occurrences-after-bigram/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings first and second, consider occurrences in some text of the form "first second third", where second comes immediately after first, and third comes immediately after second.
//
// Return an array of all the words third for each occurrence of "first second third".
//
// Example:
// Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
// Output: ["girl","student"]
//
// Constraints:
// 1 <= text.length <= 1000
// 	text consists of lowercase English letters and spaces.
// 	All the words in text are separated by a single space.
// 	1 <= first.length, second.length <= 10
// 	first and second consist of lowercase English letters.
// 	text will not have any leading or trailing spaces.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findOcurrences(char* text, char* first, char* second, int* returnSize) {
    char** result = malloc(1000 * sizeof(char*));
    *returnSize = 0;

    char* token;
    char* prev1 = NULL;
    char* prev2 = NULL;

    token = strtok(text, " ");
    while (token != NULL) {
        if (prev1 != NULL && prev2 != NULL) {
            if (strcmp(prev1, first) == 0 && strcmp(prev2, second) == 0) {
                result[*returnSize] = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(result[*returnSize], token);
                (*returnSize)++;
            }
        }
        prev1 = prev2;
        prev2 = token;
        token = strtok(NULL, " ");
    }

    return result;      
}
