// Source: https://leetcode.com/problems/number-of-ways-to-earn-points/   |   Difficulty: Hard
//
// Problem Description:
// There is a test that has n types of questions. You are given an integer target and a 0-indexed 2D integer array types where types[i] = [counti, marksi] indicates that there are counti questions of the ith type, and each one of them is worth marksi points.
//
//
//
//
// Return the number of ways you can earn exactly target points in the exam. Since the answer may be too large, return it modulo 109 + 7.
//
// Note that questions of the same type are indistinguishable.
//
//
// 	For example, if there are 3 questions of the same type, then solving the 1st and 2nd questions is the same as solving the 1st and 3rd questions, or the 2nd and 3rd questions.
//
// Example:
// Input: target = 6, types = [[6,1],[3,2],[2,3]]
// Output: 7
// Explanation: You can earn 6 points in one of the seven ways:
// - Solve 6 questions of the 0th type: 1 + 1 + 1 + 1 + 1 + 1 = 6
// - Solve 4 questions of the 0th type and 1 question of the 1st type: 1 + 1 + 1 + 1 + 2 = 6
// - Solve 2 questions of the 0th type and 2 questions of the 1st type: 1 + 1 + 2 + 2 = 6
// - Solve 3 questions of the 0th type and 1 question of the 2nd type: 1 + 1 + 1 + 3 = 6
// - Solve 1 question of the 0th type, 1 question of the 1st type and 1 question of the 2nd type: 1 + 2 + 3 = 6
// - Solve 3 questions of the 1st type: 2 + 2 + 2 = 6
// - Solve 2 questions of the 2nd type: 3 + 3 = 6
//
// Constraints:
// 1 <= target <= 1000
// 	n == types.length
// 	1 <= n <= 50
// 	types[i].length == 2
// 	1 <= counti, marksi <= 50
//

class Solution {
public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        const int MOD = 1e9 + 7;
        int n = types.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;  // One way to reach 0 points with 0 types
        
        for (int i = 1; i <= n; i++) {
            int counti = types[i - 1][0];
            int marksi = types[i - 1][1];
            
            for (int t = 0; t <= target; t++) {
                // Not using any question of this type
                dp[i][t] = dp[i - 1][t];
                
                // Using j questions of this type
                for (int j = 1; j <= counti; j++) {
                    int points = j * marksi;
                    if (t >= points) {
                        dp[i][t] = (dp[i][t] + dp[i - 1][t - points]) % MOD;
                    } else {
                        break;  // No need to check further as points will only increase
                    }
                }
            }
        }
        
        return dp[n][target];           
    }
};
