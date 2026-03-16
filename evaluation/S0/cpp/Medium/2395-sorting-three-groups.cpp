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
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(4, n));

        dp[0][0] = 0; // Base case: no elements, no operations

        for (int i = 1; i <= n; ++i) {
            int num = nums[i - 1];
            for (int state = 1; state <= 3; ++state) {
                // If current number is less than the state, we need to remove it
                if (num < state) {
                    dp[i][state] = dp[i - 1][state] + 1;
                } else {
                    // Either keep it or remove it
                    dp[i][state] = min(dp[i - 1][state], dp[i - 1][state - 1]) + (num == state ? 0 : 1);
                }
            }
        }

        return min({dp[n][1], dp[n][2], dp[n][3]});         
    }
};
