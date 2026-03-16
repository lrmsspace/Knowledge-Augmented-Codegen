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
public:
    int minCost(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            // Remove one element
            dp[i] = min(dp[i], dp[i - 1] + nums[i - 1]);

            if (i >= 2) {
                // Remove two elements
                dp[i] = min(dp[i], dp[i - 2] + max(nums[i - 1], nums[i - 2]));
            }

            if (i >= 3) {
                // Remove three elements
                int cost = max({nums[i - 1], nums[i - 2], nums[i - 3]});
                dp[i] = min(dp[i], dp[i - 3] + cost);
            }
        }

        return dp[n];           
    }
};
