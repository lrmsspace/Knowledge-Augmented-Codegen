// Source: https://leetcode.com/problems/number-of-longest-increasing-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the number of longest increasing subsequences.
//
// Notice that the sequence has to be strictly increasing.
//
// Example:
// Input: nums = [1,3,5,4,7]
// Output: 2
// Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-106 <= nums[i] <= 106
// 	The answer is guaranteed to fit inside a 32-bit integer.
//

class Solution {
    public int findNumberOfLIS(int[] nums) {
        int n = nums.length;
        int[] lengths = new int[n]; // lengths[i] = length of longest ending in nums[i]
        int[] counts = new int[n];  // counts[i] = number of longest ending in nums[i]

        for (int i = 0; i < n; i++) {
            lengths[i] = 1;
            counts[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    if (lengths[j] + 1 > lengths[i]) {
                        lengths[i] = lengths[j] + 1;
                        counts[i] = counts[j];
                    } else if (lengths[j] + 1 == lengths[i]) {
                        counts[i] += counts[j];
                    }
                }
            }
        }

        int longest = 0;
        for (int length : lengths) {
            longest = Math.max(longest, length);
        }

        int totalCount = 0;
        for (int i = 0; i < n; i++) {
            if (lengths[i] == longest) {
                totalCount += counts[i];
            }
        }

        return totalCount;          
    }
}
