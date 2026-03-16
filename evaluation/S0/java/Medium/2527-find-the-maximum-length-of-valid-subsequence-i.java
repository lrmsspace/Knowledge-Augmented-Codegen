// Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
// A subsequence sub of nums with length x is called valid if it satisfies:
//
//
// 	(sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
//
//
// Return the length of the longest valid subsequence of nums.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 4
//
// Explanation:
//
// The longest valid subsequence is [1, 2, 3, 4].
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 107
//

class Solution {
    public int maximumLength(int[] nums) {
        int evenCount = 0;
        int oddCount = 0;

        for (int num : nums) {
            if (num % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }

        return Math.max(evenCount, oddCount);           
    }
}
