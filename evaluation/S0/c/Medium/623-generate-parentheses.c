// Source: https://leetcode.com/problems/generate-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//
// Example:
// Input: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]
//
// Constraints:
// 1 <= n <= 8
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
    int maxCombinations = 1 << (2 * n); // Upper bound on combinations
    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    char* current = (char*)malloc((2 * n + 1) * sizeof(char));
    int count = 0;

    void backtrack(int open, int close, int index) {
        if (index == 2 * n) {
            current[index] = '\0';
            result[count] = (char*)malloc((2 * n + 1) * sizeof(char));
            strcpy(result[count], current);
            count++;
            return;
        }
        if (open < n) {
            current[index] = '(';
            backtrack(open + 1, close, index + 1);
        }
        if (close < open) {
            current[index] = ')';
            backtrack(open, close + 1, index + 1);
        }
    }

    backtrack(0, 0, 0);
    free(current);
    *returnSize = count;
    return result;      
}
