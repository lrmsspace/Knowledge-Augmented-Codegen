// Source: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return any array containing n unique integers such that they add up to 0.
//
// Example:
// Input: n = 5
// Output: [-7,-1,1,3,4]
// Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumZero(int n, int* returnSize) {
    int* result = (int*)malloc(n * sizeof(int));
    *returnSize = n;
    int half = n / 2;
    for (int i = 0; i < half; i++) {
        result[i] = -(i + 1);
        result[n - 1 - i] = i + 1;
    }
    if (n % 2 != 0) {
        result[half] = 0;
    }
    return result;      
}
