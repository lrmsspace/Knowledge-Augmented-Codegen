// Source: https://leetcode.com/problems/special-permutations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing n distinct positive integers. A permutation of nums is called special if:
//
//
// 	For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0.
//
//
// Return the total number of special permutations. As the answer could be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,6]
// Output: 2
// Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
//
// Constraints:
// 2 <= nums.length <= 14
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int specialPerm(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<vector<bool>> canFollow(n, vector<bool>(n, false));
        
        // Precompute which numbers can follow which
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0)) {
                    canFollow[i][j] = true;
                }
            }
        }

        // DP table: dp[mask][i] = number of ways to form a permutation using elements in 'mask' ending with element 'i'
        vector<vector<int>> dp(1 << n, vector<int>(n, 0));

        // Initialize base cases
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = 1;
        }

        // Fill DP table
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int last = 0; last < n; ++last) {
                if (!(mask & (1 << last))) continue; // last not in mask
                for (int next = 0; next < n; ++next) {
                    if (mask & (1 << next)) continue; // next already in mask
                    if (canFollow[last][next]) {
                        dp[mask | (1 << next)][next] = (dp[mask | (1 << next)][next] + dp[mask][last]) % MOD;
                    }
                }
            }
        }

        // Sum up all permutations that use all elements
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = (result + dp[(1 << n) - 1][i]) % MOD;
        }

        return result;          
    }
};
