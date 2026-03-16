// Source: https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// A binary string x is valid if all substrings of x of length 2 contain at least one "1".
//
// Return all valid strings with length n, in any order.
//
// Example:
// Input: n = 3
//
// Output: ["010","011","101","110","111"]
//
// Explanation:
//
// The valid strings of length 3 are: "010", "011", "101", "110", and "111".
//
// Constraints:
// 1 <= n <= 18
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** validStrings(int n, int* returnSize) {
    int maxSize = 1 << n; // Maximum possible binary strings of length n
    char** result = (char**)malloc(maxSize * sizeof(char*));
    *returnSize = 0;

    // Helper function to check if a binary string is valid
    int isValid(char* str, int length) {
        for (int i = 0; i < length - 1; i++) {
            if (str[i] == '0' && str[i + 1] == '0') {
                return 0; // Invalid if two adjacent zeros are found
            }
        }
        return 1; // Valid string
    }

    // Generate all binary strings of length n
    for (int i = 0; i < maxSize; i++) {
        char* str = (char*)malloc((n + 1) * sizeof(char));
        for (int j = 0; j < n; j++) {
            str[n - j - 1] = (i & (1 << j)) ? '1' : '0';
        }
        str[n] = '\0'; // Null-terminate the string

        // Check if the generated string is valid
        if (isValid(str, n)) {
            result[*returnSize] = str;
            (*returnSize)++;
        } else {
            free(str); // Free invalid strings
        }
    }

    return result;      
}
