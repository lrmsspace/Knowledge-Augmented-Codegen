// Source: https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// The value of a sequence seq of size 2 * x is defined as:
//
//
// 	(seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).
//
//
// Return the maximum value of any subsequence of nums having size 2 * k.
//
// Example:
// Input: nums = [2,6,7], k = 1
//
// Output: 5
//
// Explanation:
//
// The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.
//
// Constraints:
// 2 <= nums.length <= 400
// 	1 <= nums[i] < 27
// 	1 <= k <= nums.length / 2
//

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = dp[i + 1][j];  // Skip nums[i]
                
                if (j > 0) {
                    for (int x = i + 1; x < n; x++) {
                        int or1 = nums[i];
                        for (int p = i + 1; p <= x; p++) {
                            or1 |= nums[p];
                        }
                        
                        int or2 = 0;
                        for (int p = x + 1; p < n; p++) {
                            or2 |= nums[p];
                        }
                        
                        dp[i][j] = max(dp[i][j], (or1 ^ or2) + dp[x + 1][j - 1]);
                    }
                }
            }
        }
        
        return dp[0][k];            
    }
};
