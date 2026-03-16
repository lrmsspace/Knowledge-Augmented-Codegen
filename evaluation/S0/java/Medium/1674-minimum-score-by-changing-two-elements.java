// Source: https://leetcode.com/problems/minimum-score-by-changing-two-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
//
// 	The low score of nums is the minimum absolute difference between any two integers.
// 	The high score of nums is the maximum absolute difference between any two integers.
// 	The score of nums is the sum of the high and low scores.
//
//
// Return the minimum score after changing two elements of nums.
//
// Example:
// Input: nums = [1,4,7,8,5]
//
// Output: 3
//
// Explanation:
//
//
// 	Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
// 	The low score is the minimum absolute difference: |6 - 6| = 0.
// 	The high score is the maximum absolute difference: |8 - 5| = 3.
// 	The sum of high and low score is 3.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int minimizeSum(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        int minScore = Integer.MAX_VALUE;

        // Try all combinations of changing two elements
        for (int i = 0; i <= 2; i++) {
            int high = Math.max(nums[n - 1 - (2 - i)], nums[i + 2]);
            int low = Math.min(nums[i + 1], nums[n - 2 - (2 - i)]);
            minScore = Math.min(minScore, high - low);
        }

        return minScore;            
    }
}
