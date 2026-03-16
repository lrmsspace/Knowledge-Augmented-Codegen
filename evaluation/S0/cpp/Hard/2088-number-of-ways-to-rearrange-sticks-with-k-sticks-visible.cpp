// Source: https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/   |   Difficulty: Hard
//
// Problem Description:
// There are n uniquely-sized sticks whose lengths are integers from 1 to n. You want to arrange the sticks such that exactly k sticks are visible from the left. A stick is visible from the left if there are no longer sticks to the left of it.
//
//
// 	For example, if the sticks are arranged [1,3,2,5,4], then the sticks with lengths 1, 3, and 5 are visible from the left.
//
//
// Given n and k, return the number of such arrangements. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, k = 2
// Output: 3
// Explanation: [1,3,2], [2,3,1], and [2,1,3] are the only arrangements such that exactly 2 sticks are visible.
// The visible sticks are underlined.
//
// Constraints:
// 1 <= n <= 1000
// 	1 <= k <= n
//

class Solution {
public:
    int rearrangeSticks(int n, int k) {
        const int MOD = 1e9 + 7;
        // dp[i][j]: number of ways to arrange i sticks with j visible
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
        
        dp[1][1] = 1;  // Base case: 1 stick, 1 visible
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                // Case 1: Place the longest stick at the front (visible)
                dp[i][j] = dp[i - 1][j - 1] % MOD;
                
                // Case 2: Place the longest stick not at the front (not visible)
                dp[i][j] = (dp[i][j] + dp[i - 1][j] * (i - 1)) % MOD;
            }
        }
        
        return dp[n][k];            
    }
};
