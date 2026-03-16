// Source: https://leetcode.com/problems/count-the-number-of-winning-sequences/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob are playing a fantasy battle game consisting of n rounds where they summon one of three magical creatures each round: a Fire Dragon, a Water Serpent, or an Earth Golem. In each round, players simultaneously summon their creature and are awarded points as follows:
//
//
// 	If one player summons a Fire Dragon and the other summons an Earth Golem, the player who summoned the Fire Dragon is awarded a point.
// 	If one player summons a Water Serpent and the other summons a Fire Dragon, the player who summoned the Water Serpent is awarded a point.
// 	If one player summons an Earth Golem and the other summons a Water Serpent, the player who summoned the Earth Golem is awarded a point.
// 	If both players summon the same creature, no player is awarded a point.
//
//
// You are given a string s consisting of n characters 'F', 'W', and 'E', representing the sequence of creatures Alice will summon in each round:
//
//
// 	If s[i] == 'F', Alice summons a Fire Dragon.
// 	If s[i] == 'W', Alice summons a Water Serpent.
// 	If s[i] == 'E', Alice summons an Earth Golem.
//
//
// Bob’s sequence of moves is unknown, but it is guaranteed that Bob will never summon the same creature in two consecutive rounds. Bob beats Alice if the total number of points awarded to Bob after n rounds is strictly greater than the points awarded to Alice.
//
// Return the number of distinct sequences Bob can use to beat Alice.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "FFF"
//
// Output: 3
//
// Explanation:
//
// Bob can beat Alice by making one of the following sequences of moves: "WFW", "FWF", or "WEW". Note that other winning sequences like "WWE" or "EWW" are invalid since Bob cannot make the same move twice in a row.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is one of 'F', 'W', or 'E'.
//

class Solution {
public:
    int countWinningSequences(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        // dp[i][j][k]: number of ways up to round i, Bob's last creature j, score difference k
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(3, vector<int>(2 * n + 1, 0)));
        
        // Initial state: before any rounds, last creature is invalid (-1), score difference is 0
        for (int j = 0; j < 3; ++j) {
            dp[0][j][n] = 1; // score difference offset by n
        }
        
        for (int i = 0; i < n; ++i) {
            for (int lastBob = 0; lastBob < 3; ++lastBob) {
                for (int diff = 0; diff <= 2 * n; ++diff) {
                    if (dp[i][lastBob][diff] == 0) continue;
                    
                    for (int bobCreature = 0; bobCreature < 3; ++bobCreature) {
                        if (bobCreature == lastBob) continue; // Bob cannot summon the same creature consecutively
                        
                        int newDiff = diff;
                        char aliceCreature = s[i];
                        
                        // Determine score change
                        if ((aliceCreature == 'F' && bobCreature == 1) || // Bob: Water Serpent
                            (aliceCreature == 'W' && bobCreature == 2) || // Bob: Earth Golem
                            (aliceCreature == 'E' && bobCreature == 0)) { // Bob: Fire Dragon
                            newDiff++; // Bob wins this round
                        } else if ((aliceCreature == 'F' && bobCreature == 2) || // Bob: Earth Golem
                                   (aliceCreature == 'W' && bobCreature == 0) || // Bob: Fire Dragon
                                   (aliceCreature == 'E' && bobCreature == 1)) { // Bob: Water Serpent
                            newDiff--; // Alice wins this round
                        }
                        
                        dp[i + 1][bobCreature][newDiff] = (dp[i + 1][bobCreature][newDiff] + dp[i][lastBob][diff]) % MOD;
                    }
                }
            }
        }
        
        int result = 0;
        for (int lastBob = 0; lastBob < 3; ++lastBob) {
            for (int diff = n + 1; diff <= 2 * n; ++diff) {
                result = (result + dp[n][lastBob][diff]) % MOD;
            }
        }
        
        return result;
    }
};
