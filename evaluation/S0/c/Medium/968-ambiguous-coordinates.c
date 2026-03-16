// Source: https://leetcode.com/problems/ambiguous-coordinates/   |   Difficulty: Medium
//
// Problem Description:
// We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then, we removed all commas, decimal points, and spaces and ended up with the string s.
//
//
// 	For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s = "(205)".
//
//
// Return a list of strings representing all possibilities for what our original coordinates could have been.
//
// Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with fewer digits. Also, a decimal point within a number never occurs without at least one digit occurring before it, so we never started with numbers like ".1".
//
// The final answer list can be returned in any order. All coordinates in the final answer have exactly one space between them (occurring after the comma.)
//
// Example:
// Input: s = "(123)"
// Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
//
// Constraints:
// 4 <= s.length <= 12
// 	s[0] == '(' and s[s.length - 1] == ')'.
// 	The rest of s are digits.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** ambiguousCoordinates(char* s, int* returnSize) {
    int len = strlen(s) - 2; // exclude parentheses
    char** result = (char**)malloc(1000 * sizeof(char*));
    *returnSize = 0;

    // Helper function to generate valid number representations
    void generateNumbers(char* str, int start, int end, char*** nums, int* count) {
        int length = end - start + 1;
        char buffer[15];

        // No decimal point
        if (length == 1 || str[start] != '0') {
            strncpy(buffer, str + start, length);
            buffer[length] = '\0';
            (*nums)[(*count)++] = strdup(buffer);
        }

        // With decimal point
        for (int i = 1; i < length; i++) {
            if ((i > 1 && str[start] == '0') || (length - i > 1 && str[start + i] == '0')) continue;
            strncpy(buffer, str + start, i);
            buffer[i] = '.';
            strncpy(buffer + i + 1, str + start + i, length - i);
            buffer[length + 1] = '\0';
            (*nums)[(*count)++] = strdup(buffer);
        }
    }

    // Iterate through possible split points
    for (int i = 1; i < len; i++) {
        char** leftNums = (char**)malloc(100 * sizeof(char*));
        char** rightNums = (char**)malloc(100 * sizeof(char*));
        int leftCount = 0, rightCount = 0;

        generateNumbers(s, 1, i, &leftNums, &leftCount);
        generateNumbers(s, i + 1, len, &rightNums, &rightCount);

        for (int l = 0; l < leftCount; l++) {
            for (int r = 0; r < rightCount; r++) {
                char buffer[30];
                sprintf(buffer, "(%s, %s)", leftNums[l], rightNums[r]);
                result[(*returnSize)++] = strdup(buffer);
            }
        }

        for (int j = 0; j < leftCount; j++) free(leftNums[j]);
        for (int j = 0; j < rightCount; j++) free(rightNums[j]);
        free(leftNums);
        free(rightNums);
    }
    return result;
}
