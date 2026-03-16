// Source: https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/   |   Difficulty: Hard
//
// Problem Description:
// There are n people and 40 types of hats labeled from 1 to 40.
//
// Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.
//
// Return the number of ways that n people can wear different hats from each other.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: hats = [[3,4],[4,5],[5]]
// Output: 1
// Explanation: There is only one way to choose hats given the conditions. 
// First person choose hat 3, Second person choose hat 4 and last one hat 5.
//
// Constraints:
// n == hats.length
// 	1 <= n <= 10
// 	1 <= hats[i].length <= 40
// 	1 <= hats[i][j] <= 40
// 	hats[i] contains a list of unique integers.
//

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        const int MOD = 1e9 + 7;
        int n = hats.size();
        vector<vector<int>> hatToPeople(41);
        
        // Map hats to people
        for (int person = 0; person < n; person++) {
            for (int hat : hats[person]) {
                hatToPeople[hat].push_back(person);
            }
        }
        
        // DP array
        vector<int> dp(1 << n, 0);
        dp[0] = 1;  // One way to assign no hats
        
        // Iterate over each hat
        for (int hat = 1; hat <= 40; hat++) {
            vector<int> newDp(dp);
            
            // For each subset of people
            for (int mask = 0; mask < (1 << n); mask++) {
                if (dp[mask] == 0) continue;
                
                // Try to assign this hat to each person who likes it
                for (int person : hatToPeople[hat]) {
                    if ((mask & (1 << person)) == 0) {  // If person is not assigned a hat yet
                        int newMask = mask | (1 << person);
                        newDp[newMask] = (newDp[newMask] + dp[mask]) % MOD;
                    }
                }
            }
            
            dp = newDp;
        }
        
        return dp[(1 << n) - 1];  // All people have hats assigned          
    }
};
