// Source: https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array nums. Your task is to select a complete subset from nums where every pair of selected indices multiplied is a perfect square,. i. e. if you select ai and aj, i * j must be a perfect square.
//
// Return the sum of the complete subset with the maximum sum.
//
// Example:
// Input: nums = [8,7,3,5,7,2,4,9]
//
// Output: 16
//
// Explanation:
//
// We select elements at indices 2 and 8 and 2 * 8 is a perfect square.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= nums[i] <= 109
//

class Solution {
    public long maximumSum(List<Integer> nums) {
        int n = nums.size();
        long[] dp = new long[n + 1];
        long maxSum = 0;

        for (int i = 1; i <= n; i++) {
            dp[i] = nums.get(i - 1);
            for (int j = 1; j * j <= i; j++) {
                int k = i / (j * j);
                if (k * j * j == i) {
                    dp[i] = Math.max(dp[i], dp[k] + nums.get(i - 1));
                }
            }
            maxSum = Math.max(maxSum, dp[i]);
        }

        return maxSum;          
    }
}
