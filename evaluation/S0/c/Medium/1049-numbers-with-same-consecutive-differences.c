// Source: https://leetcode.com/problems/numbers-with-same-consecutive-differences/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return an array of all the integers of length n where the difference between every two consecutive digits is k. You may return the answer in any order.
//
// Note that the integers should not have leading zeros. Integers as 02 and 043 are not allowed.
//
// Example:
// Input: n = 3, k = 7
// Output: [181,292,707,818,929]
// Explanation: Note that 070 is not a valid number, because it has leading zeroes.
//
// Constraints:
// 2 <= n <= 9
// 	0 <= k <= 9
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numsSameConsecDiff(int n, int k, int* returnSize) {
    int maxSize = 10000; // Initial estimate for maximum size
    int* result = (int*)malloc(maxSize * sizeof(int));
    *returnSize = 0;

    void dfs(int num, int length) {
        if (length == n) {
            if (*returnSize >= maxSize) {
                maxSize *= 2;
                result = (int*)realloc(result, maxSize * sizeof(int));
            }
            result[(*returnSize)++] = num;
            return;
        }

        int lastDigit = num % 10;

        if (lastDigit + k < 10) {
            dfs(num * 10 + (lastDigit + k), length + 1);
        }
        if (k != 0 && lastDigit - k >= 0) {
            dfs(num * 10 + (lastDigit - k), length + 1);
        }
    }

    for (int i = 1; i <= 9; i++) {
        dfs(i, 1);
    }

    return result;      
}
