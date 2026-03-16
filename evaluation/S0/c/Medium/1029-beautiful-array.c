// Source: https://leetcode.com/problems/beautiful-array/   |   Difficulty: Medium
//
// Problem Description:
// An array nums of length n is beautiful if:
//
//
// 	nums is a permutation of the integers in the range [1, n].
// 	For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k] == nums[i] + nums[j].
//
//
// Given the integer n, return any beautiful array nums of length n. There will be at least one valid answer for the given n.
//
// Example:
// Input: n = 4
// Output: [2,1,4,3]
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* beautifulArray(int n, int* returnSize) {
    int *res = (int *)malloc(sizeof(int) * n);
    *returnSize = n;

    res[0] = 1;
    int size = 1;

    while (size < n) {
        // Generate odd numbers
        for (int i = 0; i < size; i++) {
            int val = res[i] * 2 - 1;
            if (val <= n) {
                res[size++] = val;
            }
        }
        // Generate even numbers
        for (int i = 0; i < size / 2; i++) {
            int val = res[i] * 2;
            if (val <= n) {
                res[size++] = val;
            }
        }
    }

    return res;     
}
