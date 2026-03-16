// Source: https://leetcode.com/problems/find-the-most-competitive-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and a positive integer k, return the most competitive subsequence of nums of size k.
//
// An array's subsequence is a resulting sequence obtained by erasing some (possibly zero) elements from the array.
//
// We define that a subsequence a is more competitive than a subsequence b (of the same length) if in the first position where a and b differ, subsequence a has a number less than the corresponding number in b. For example, [1,3,4] is more competitive than [1,3,5] because the first position they differ is at the final number, and 4 is less than 5.
//
// Example:
// Input: nums = [3,5,2,6], k = 2
// Output: [2,6]
// Explanation: Among the set of every possible subsequence: {[3,5], [3,2], [3,6], [5,2], [5,6], [2,6]}, [2,6] is the most competitive.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	1 <= k <= nums.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* mostCompetitive(int* nums, int numsSize, int k, int* returnSize) {
    int* stack = (int*)malloc(sizeof(int) * k);
    int top = -1;
    int toRemove = numsSize - k;

    for (int i = 0; i < numsSize; i++) {
        while (top >= 0 && stack[top] > nums[i] && toRemove > 0) {
            top--;
            toRemove--;
        }
        if (top + 1 < k) {
            stack[++top] = nums[i];
        } else {
            toRemove--;
        }
    }

    *returnSize = k;
    return stack;       
}
