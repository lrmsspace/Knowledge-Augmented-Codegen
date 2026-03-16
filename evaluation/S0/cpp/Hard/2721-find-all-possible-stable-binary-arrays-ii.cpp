// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given 3 positive integers zero, one, and limit.
//
// A binary array arr is called stable if:
//
//
// 	The number of occurrences of 0 in arr is exactly zero.
// 	The number of occurrences of 1 in arr is exactly one.
// 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
//
//
// Return the total number of stable binary arrays.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: zero = 1, one = 1, limit = 2
//
// Output: 2
//
// Explanation:
//
// The two possible stable binary arrays are [1,0] and [0,1].
//
// Constraints:
// 1 <= zero, one, limit <= 1000
//

class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        const int MOD = 1e9 + 7;
        vector<vector<vector<int>>> dp(zero + 1, vector<vector<int>>(one + 1, vector<int>(2, 0)));
        
        // Base cases
        dp[0][0][0] = 1;
        dp[0][0][1] = 1;
        
        for (int z = 0; z <= zero; z++) {
            for (int o = 0; o <= one; o++) {
                for (int last = 0; last <= 1; last++) {
                    if (z == 0 && o == 0) continue;
                    
                    // Add a 0
                    if (z > 0) {
                        if (last == 1) {
                            dp[z][o][0] = (dp[z][o][0] + dp[z - 1][o][1]) % MOD;
                        } else {
                            for (int len = 1; len <= limit && z - len >= 0; len++) {
                                dp[z][o][0] = (dp[z][o][0] + dp[z - len][o][1]) % MOD;
                            }
                        }
                    }
                    
                    // Add a 1
                    if (o > 0) {
                        if (last == 0) {
                            dp[z][o][1] = (dp[z][o][1] + dp[z][o - 1][0]) % MOD;
                        } else {
                            for (int len = 1; len <= limit && o - len >= 0; len++) {
                                dp[z][o][1] = (dp[z][o][1] + dp[z][o - len][0]) % MOD;
                            }
                        }
                    }
                }
            }
        }
        
        return (dp[zero][one][0] + dp[zero][one][1]) % MOD;         
    }
};
