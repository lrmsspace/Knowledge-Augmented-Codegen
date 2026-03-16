// Source: https://leetcode.com/problems/counting-bits/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
//
// Example:
// Input: n = 2
// Output: [0,1,1]
// Explanation:
// 0 --> 0
// 1 --> 1
// 2 --> 10
//
// Constraints:
// 0 <= n <= 105
//
//
//  
// Follow up:
//
//
// 	It is very easy to come up with a solution with a runtime of O(n log n). Can you do it in linear time O(n) and possibly in a single pass?
// 	Can you do it without using any built-in function (i.e., like __builtin_popcount in C++)?
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    int *ans = (int *)malloc((n + 1) * sizeof(int));
    ans[0] = 0;
    *returnSize = n + 1;

    for (int i = 1; i <= n; i++) {
        ans[i] = ans[i >> 1] + (i & 1);
    }

    return ans;     
}
