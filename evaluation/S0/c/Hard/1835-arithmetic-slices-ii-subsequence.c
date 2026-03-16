// Source: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of all the arithmetic subsequences of nums.
//
// A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
//
//
// 	For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
// 	For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// The test cases are generated so that the answer fits in 32-bit integer.
//
// Example:
// Input: nums = [2,4,6,8,10]
// Output: 7
// Explanation: All arithmetic subsequence slices are:
// [2,4,6]
// [4,6,8]
// [6,8,10]
// [2,4,6,8]
// [4,6,8,10]
// [2,4,6,8,10]
// [2,6,10]
//
// Constraints:
// 1  <= nums.length <= 1000
// 	-231 <= nums[i] <= 231 - 1
//

int numberOfArithmeticSlices(int* nums, int numsSize) {
    if (numsSize < 3) return 0;
    int **dp = (int**)malloc(numsSize * sizeof(int*));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = (int*)calloc(numsSize, sizeof(int));
    }
    int result = 0;
    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            long diff = (long)nums[i] - (long)nums[j];
            if (diff < INT_MIN || diff > INT_MAX) continue;
            int d = (int)diff;
            dp[i][j] = 0;
            for (int k = 0; k < j; k++) {
                if ((long)nums[j] - (long)nums[k] == (long)d) {
                    dp[i][j] += dp[j][k] + 1;
                }
            }
            result += dp[i][j];
        }
    }
    for (int i = 0; i < numsSize; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;      
}
