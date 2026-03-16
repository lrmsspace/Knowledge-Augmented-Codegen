// Source: https://leetcode.com/problems/sorting-three-groups/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. Each element in nums is 1, 2 or 3. In each operation, you can remove an element from nums. Return the minimum number of operations to make nums non-decreasing.
//
// Example:
// Input: nums = [2,1,3,2,1]
//
// Output: 3
//
// Explanation:
//
// One of the optimal solutions is to remove nums[0], nums[2] and nums[3].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 3
//
//
//  
// Follow-up: Can you come up with an algorithm that runs in O(n) time complexity?
//

class Solution {
    public int minimumOperations(List<Integer> nums) {
        int n = nums.size();
        int[][] dp = new int[n + 1][4];

        for (int i = 1; i <= n; i++) {
            int num = nums.get(i - 1);
            for (int j = 1; j <= 3; j++) {
                dp[i][j] = dp[i - 1][j] + (num == j ? 0 : 1);
                if (j > 1) {
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1] + (num == j ? 0 : 1));
                }
            }
        }

        return Math.min(dp[n][1], Math.min(dp[n][2], dp[n][3]));            
    }
}
