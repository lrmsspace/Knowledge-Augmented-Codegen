// Source: https://leetcode.com/problems/simplified-fractions/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all simplified fractions between 0 and 1 (exclusive) such that the denominator is less-than-or-equal-to n. You can return the answer in any order.
//
// Example:
// Input: n = 2
// Output: ["1/2"]
// Explanation: "1/2" is the only unique fraction with a denominator less-than-or-equal-to 2.
//
// Constraints:
// 1 <= n <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** simplifiedFractions(int n, int* returnSize) {
    char **result = malloc(0);
    *returnSize = 0;

    for (int den = 2; den <= n; den++) {
        for (int num = 1; num < den; num++) {
            int a = num, b = den;
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            if (a == 1) {
                result = realloc(result, sizeof(char*) * (*returnSize + 1));
                result[*returnSize] = malloc(8 * sizeof(char));
                sprintf(result[*returnSize], "%d/%d", num, den);
                (*returnSize)++;
            }
        }
    }

    return result;      
}
