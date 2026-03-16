// Source: https://leetcode.com/problems/find-minimum-cost-to-remove-array-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. Your task is to remove all elements from the array by performing one of the following operations at each step until nums is empty:
//
//
// 	Choose any two elements from the first three elements of nums and remove them. The cost of this operation is the maximum of the two elements removed.
// 	If fewer than three elements remain in nums, remove all the remaining elements in a single operation. The cost of this operation is the maximum of the remaining elements.
//
//
// Return the minimum cost required to remove all the elements.
//
// Example:
// Input: nums = [6,2,8,4]
//
// Output: 12
//
// Explanation:
//
// Initially, nums = [6, 2, 8, 4].
//
//
// 	In the first operation, remove nums[0] = 6 and nums[2] = 8 with a cost of max(6, 8) = 8. Now, nums = [2, 4].
// 	In the second operation, remove the remaining elements with a cost of max(2, 4) = 4.
//
//
// The cost to remove all elements is 8 + 4 = 12. This is the minimum cost to remove all elements in nums. Hence, the output is 12.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 106
//

class Solution {
    public int minCost(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n + 1];
        dp[0] = 0;
        dp[1] = nums[0];

        if (n >= 2) {
            dp[2] = Math.max(nums[0], nums[1]);
        }

        for (int i = 3; i <= n; i++) {
            int costRemoveFirstTwo = dp[i - 2] + Math.max(nums[i - 1], nums[i - 2]);
            int costRemoveFirstAndThird = dp[i - 2] + Math.max(nums[i - 1], nums[i - 3]);
            dp[i] = Math.min(costRemoveFirstTwo, costRemoveFirstAndThird);
        }

        return dp[n];           
    }
}
