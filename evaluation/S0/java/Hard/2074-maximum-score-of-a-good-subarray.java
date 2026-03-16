// Source: https://leetcode.com/problems/maximum-score-of-a-good-subarray/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums (0-indexed) and an integer k.
//
// The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1). A good subarray is a subarray where i <= k <= j.
//
// Return the maximum possible score of a good subarray.
//
// Example:
// Input: nums = [1,4,3,7,4,5], k = 3
// Output: 15
// Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (5-1+1) = 3 * 5 = 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 2 * 104
// 	0 <= k < nums.length
//

class Solution {
    public int maximumScore(int[] nums, int k) {
        int left = k;
        int right = k;
        int minVal = nums[k];
        int maxScore = minVal;

        while (left > 0 || right < nums.length - 1) {
            if (right < nums.length - 1 && (left == 0 || nums[right + 1] >= nums[left - 1])) {
                right++;
                minVal = Math.min(minVal, nums[right]);
            } else {
                left--;
                minVal = Math.min(minVal, nums[left]);
            }
            maxScore = Math.max(maxScore, minVal * (right - left + 1));
        }

        return maxScore;            
    }
}
