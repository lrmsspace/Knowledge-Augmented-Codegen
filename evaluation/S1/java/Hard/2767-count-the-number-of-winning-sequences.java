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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int getPoint(char aliceMove, int bobMove) {
        // Bob's moves: 0 - Fire Dragon (F), 1 - Water Serpent (W), 2 - Earth Golem (E)
        if (aliceMove == 'F') {
            return bobMove == 1 ? 1 : (bobMove == 2 ? 0 : 0);
        } else if (aliceMove == 'W') {
            return bobMove == 2 ? 1 : (bobMove == 0 ? 0 : 0);
        } else { // aliceMove == 'E'
            return bobMove == 0 ? 1 : (bobMove == 1 ? 0 : 0);
        }
    }
    public int countWinningSequences(String s) {
        int MOD = 1_000_000_007;
        int n = s.length();
        long[][][] dp = new long[n + 1][n + 1][3];

        for (int j = 0; j < 3; j++) {
            dp[0][0][j] = 1;
        }

        for (int i = 1; i <= n; i++) {
            char aliceMove = s.charAt(i - 1);
            for (int j = 0; j <= i; j++) {
                for (int lastBobMove = 0; lastBobMove < 3; lastBobMove++) {
                    for (int bobMove = 0; bobMove < 3; bobMove++) {
                        if (bobMove == lastBobMove) continue;

                        int alicePoint = getPoint(aliceMove, bobMove);
                        int newJ = j + alicePoint;

                        dp[i][newJ][bobMove] = (dp[i][newJ][bobMove] + dp[i - 1][j][lastBobMove]) % MOD;
                    }
                }
            }
        }

        long result = 0;
        for (int j = (n / 2) + 1; j <= n; j++) {
            for (int bobMove = 0; bobMove < 3; bobMove++) {
                result = (result + dp[n][j][bobMove]) % MOD;
            }
        }

        return (int) result;            
    }
}
