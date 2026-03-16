// Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
//
// For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
//
// Return the sum of the answers to all queries.
//
// Since the final answer may be very large, return it modulo 109 + 7.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
//
// Output: 21
//
// Explanation:
// After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
// After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-105 <= nums[i] <= 105
// 	1 <= queries.length <= 5 * 104
// 	queries[i] == [posi, xi]
// 	0 <= posi <= nums.length - 1
// 	-105 <= xi <= 105
//

int maximumSumSubsequence(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    const int MOD = 1000000007;

    /* Helper function to compute max sum of non-adjacent elements */
    int maxSumNonAdjacent(int* arr, int size) {
        int incl = 0; // Max sum including the previous element
        int excl = 0; // Max sum excluding the previous element
        for (int i = 0; i < size; i++) {
            int new_excl = (incl > excl) ? incl : excl;
            incl = excl + (arr[i] > 0 ? arr[i] : 0);
            excl = new_excl;
        }
        return (incl > excl) ? incl : excl;
    }

    long long totalSum = 0;
    for (int q = 0; q < queriesSize; q++) {
        int pos = queries[q][0];
        int val = queries[q][1];
        int originalVal = nums[pos];
        nums[pos] = val;
        int currentMaxSum = maxSumNonAdjacent(nums, numsSize);
        totalSum = (totalSum + currentMaxSum) % MOD;
        nums[pos] = originalVal; // Restore original value
    }

    return (int)totalSum;       
}
