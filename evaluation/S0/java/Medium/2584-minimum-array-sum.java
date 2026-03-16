// Source: https://leetcode.com/problems/minimum-array-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and three integers k, op1, and op2.
//
// You can perform the following operations on nums:
//
//
// 	Operation 1: Choose an index i and divide nums[i] by 2, rounding up to the nearest whole number. You can perform this operation at most op1 times, and not more than once per index.
// 	Operation 2: Choose an index i and subtract k from nums[i], but only if nums[i] is greater than or equal to k. You can perform this operation at most op2 times, and not more than once per index.
//
//
// Note: Both operations can be applied to the same index, but at most once each.
//
// Return the minimum possible sum of all elements in nums after performing any number of operations.
//
// Example:
// Input: nums = [2,8,3,19,3], k = 3, op1 = 1, op2 = 1
//
// Output: 23
//
// Explanation:
//
//
// 	Apply Operation 2 to nums[1] = 8, making nums[1] = 5.
// 	Apply Operation 1 to nums[3] = 19, making nums[3] = 10.
// 	The resulting array becomes [2, 5, 3, 10, 3], which has the minimum possible sum of 23 after applying the operations.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 105
// 	0 <= k <= 105
// 	0 <= op1, op2 <= nums.length
//

class Solution {
    public int minArraySum(int[] nums, int k, int op1, int op2) {
        int n = nums.length;
        int[][] dp = new int[n + 1][(op1 + 1) * (op2 + 1)];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= op1; j++) {
                for (int l = 0; l <= op2; l++) {
                    int idx = j * (op2 + 1) + l;
                    dp[i][idx] = dp[i + 1][idx] + nums[i];
                    if (j > 0) {
                        int newVal = (nums[i] + 1) / 2;
                        dp[i][idx] = Math.min(dp[i][idx], dp[i + 1][(j - 1) * (op2 + 1) + l] + newVal);
                    }
                    if (l > 0 && nums[i] >= k) {
                        int newVal = nums[i] - k;
                        dp[i][idx] = Math.min(dp[i][idx], dp[i + 1][j * (op2 + 1) + (l - 1)] + newVal);
                    }
                    if (j > 0 && l > 0 && nums[i] >= k) {
                        int newVal = (nums[i] - k + 1) / 2;
                        dp[i][idx] = Math.min(dp[i][idx], dp[i + 1][(j - 1) * (op2 + 1) + (l - 1)] + newVal);
                    }
                }
            }
        }
        return dp[0][op1 * (op2 + 1) + op2];            
    }
}
