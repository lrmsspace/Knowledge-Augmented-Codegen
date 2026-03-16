// Source: https://leetcode.com/problems/painting-the-walls/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays, cost and time, of size n representing the costs and the time taken to paint n different walls respectively. There are two painters available:
//
//
// 	A paid painter that paints the ith wall in time[i] units of time and takes cost[i] units of money.
// 	A free painter that paints any wall in 1 unit of time at a cost of 0. But the free painter can only be used if the paid painter is already occupied.
//
//
// Return the minimum amount of money required to paint the n walls.
//
// Example:
// Input: cost = [1,2,3,2], time = [1,2,3,2]
// Output: 3
// Explanation: The walls at index 0 and 1 will be painted by the paid painter, and it will take 3 units of time; meanwhile, the free painter will paint the walls at index 2 and 3, free of cost in 2 units of time. Thus, the total cost is 1 + 2 = 3.
//
// Constraints:
// 1 <= cost.length <= 500
// 	cost.length == time.length
// 	1 <= cost[i] <= 106
// 	1 <= time[i] <= 500
//

class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        int maxTime = 0;
        for (int t : time) {
            maxTime += t;
        }
        
        // dp[i][j]: minimum cost to paint first i walls in j time
        vector<vector<long long>> dp(n + 1, vector<long long>(maxTime + 1, LLONG_MAX));
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= maxTime; j++) {
                // Option 1: use paid painter for wall i-1
                if (j >= time[i - 1] && dp[i - 1][j - time[i - 1]] != LLONG_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - time[i - 1]] + cost[i - 1]);
                }
                
                // Option 2: use free painter for wall i-1
                if (j >= 1 && dp[i - 1][j - 1] != LLONG_MAX) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
            }
        }
        
        long long result = LLONG_MAX;
        for (int j = 0; j <= maxTime; j++) {
            result = min(result, dp[n][j]);
        }
        
        return (int)result;         
    }
};
