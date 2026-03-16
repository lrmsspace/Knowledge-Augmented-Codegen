// Source: https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, x, and y.
//
// An event is being held for n performers. When a performer arrives, they are assigned to one of the x stages. All performers assigned to the same stage will perform together as a band, though some stages might remain empty.
//
// After all performances are completed, the jury will award each band a score in the range [1, y].
//
// Return the total number of possible ways the event can take place.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note that two events are considered to have been held differently if either of the following conditions is satisfied:
//
//
// 	Any performer is assigned a different stage.
// 	Any band is awarded a different score.
//
// Example:
// Input: n = 1, x = 2, y = 3
//
// Output: 6
//
// Explanation:
//
//
// 	There are 2 ways to assign a stage to the performer.
// 	The jury can award a score of either 1, 2, or 3 to the only band.
//
// Constraints:
// 1 <= n, x, y <= 1000
//

class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        const int MOD = 1e9 + 7;
        vector<vector<long long>> dp(n + 1, vector<long long>(x + 1, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= x; j++) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] * j) % MOD;
            }
        }
        
        long long result = 0;
        for (int k = 1; k <= x; k++) {
            long long ways = dp[n][k];
            long long scoreWays = 1;
            for (int s = 0; s < k; s++) {
                scoreWays = (scoreWays * y) % MOD;
            }
            result = (result + ways * scoreWays) % MOD;
        }
        
        return (int)result;         
    }
};
