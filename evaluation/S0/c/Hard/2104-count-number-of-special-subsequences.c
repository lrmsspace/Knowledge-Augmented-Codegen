// Source: https://leetcode.com/problems/count-number-of-special-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// A sequence is special if it consists of a positive number of 0s, followed by a positive number of 1s, then a positive number of 2s.
//
//
// 	For example, [0,1,2] and [0,0,1,1,1,2] are special.
// 	In contrast, [2,1,0], [1], and [0,1,2,0] are not special.
//
//
// Given an array nums (consisting of only integers 0, 1, and 2), return the number of different subsequences that are special. Since the answer may be very large, return it modulo 109 + 7.
//
// A subsequence of an array is a sequence that can be derived from the array by deleting some or no elements without changing the order of the remaining elements. Two subsequences are different if the set of indices chosen are different.
//
// Example:
// Input: nums = [0,1,2,2]
// Output: 3
// Explanation: The special subsequences are bolded [0,1,2,2], [0,1,2,2], and [0,1,2,2].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 2
//

int countSpecialSubsequences(int* nums, int numsSize) {
    const int MOD = 1000000007;
    long long count0 = 0, count1 = 0, count2 = 0;

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            count0 = (2 * count0 + 1) % MOD;
        } else if (nums[i] == 1) {
            count1 = (2 * count1 + count0) % MOD;
        } else if (nums[i] == 2) {
            count2 = (2 * count2 + count1) % MOD;
        }
    }

    return (int)count2;     
}
