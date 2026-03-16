// Source: https://leetcode.com/problems/longest-increasing-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// Find the longest subsequence of nums that meets the following requirements:
//
//
// 	The subsequence is strictly increasing and
// 	The difference between adjacent elements in the subsequence is at most k.
//
//
// Return the length of the longest subsequence that meets the requirements.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [4,2,1,4,3,4,5,8,15], k = 3
// Output: 5
// Explanation:
// The longest subsequence that meets the requirements is [1,3,4,5,8].
// The subsequence has a length of 5, so we return 5.
// Note that the subsequence [1,3,4,5,8,15] does not meet the requirements because 15 - 8 = 7 is larger than 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 105
//

class Solution {
    public int lengthOfLIS(int[] nums, int k) {
        int maxNum = 0;
        for (int num : nums) {
            maxNum = Math.max(maxNum, num);
        }

        SegmentTree segmentTree = new SegmentTree(maxNum + 1);
        int result = 0;

        for (int num : nums) {
            int left = Math.max(0, num - k);
            int right = num - 1;
            int bestPrev = segmentTree.query(left, right);
            int currLength = bestPrev + 1;
            segmentTree.update(num, currLength);
            result = Math.max(result, currLength);
        }

        return result;          
    }
}
