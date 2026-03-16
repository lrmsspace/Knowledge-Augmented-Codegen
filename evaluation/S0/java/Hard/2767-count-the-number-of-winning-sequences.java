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
    public int countWinningSequences(String s) {
        int n = s.length();
        int mod = (int)1e9 + 7;

        // dp[i][j][k]: number of ways up to round i, with score difference j (Bob - Alice), and Bob's last move k
        int[][][] dp = new int[n + 1][2 * n + 1][3];
        dp[0][n][0] = dp[0][n][1] = dp[0][n][2] = 1; // Base case

        for (int i = 1; i <= n; i++) {
            char aliceMove = s.charAt(i - 1);
            for (int scoreDiff = -n; scoreDiff <= n; scoreDiff++) {
                for (int lastMove = 0; lastMove < 3; lastMove++) {
                    for (int bobMove = 0; bobMove < 3; bobMove++) {
                        if (bobMove == lastMove) continue; // Bob cannot repeat the same move

                        int newScoreDiff = scoreDiff;
                        if (beats(bobMove, aliceMove)) newScoreDiff++;
                        else if (beats(aliceMove, bobMove)) newScoreDiff--;

                        dp[i][newScoreDiff + n][bobMove] = (dp[i][newScoreDiff + n][bobMove] + dp[i - 1][scoreDiff + n][lastMove]) % mod;
                    }
                }
            }
        }

        int result = 0;
        for (int scoreDiff = 1; scoreDiff <= n; scoreDiff++) {
            for (int lastMove = 0; lastMove < 3; lastMove++) {
                result = (result + dp[n][scoreDiff + n][lastMove]) % mod;
            }
        }

        return result;          
    }
}
