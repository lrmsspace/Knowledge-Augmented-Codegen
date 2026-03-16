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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countWinningSequences(char* s) {
    const int MOD = 1000000007;
    int n = 0;
    while (s[n] != '\0') n++;

    /* dp[i][j][k]: number of ways up to round i, with score difference j (-n to n mapped to 0 to 2n), last move k (0:F,1:W,2:E) */
    int dp[1001][2001][3];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= 2 * n; j++)
            for (int k = 0; k < 3; k++)
                dp[i][j][k] = 0;

    /* Initial state: before first round, score difference 0, last move none */
    dp[0][n][0] = 1;
    dp[0][n][1] = 1;
    dp[0][n][2] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 2 * n; j++) {
            for (int last = 0; last < 3; last++) {
                if (dp[i][j][last] == 0) continue;
                for (int move = 0; move < 3; move++) {
                    if (move == last) continue; /* cannot repeat last move */
                    int scoreDiff = j;
                    /* Update score difference based on Alice's move */
                    if (s[i] == 'F') {
                        if (move == 1) scoreDiff++; /* W beats F */
                        else if (move == 2) scoreDiff--; /* E loses to F */
                    } else if (s[i] == 'W') {
                        if (move == 2) scoreDiff++; /* E beats W */
                        else if (move == 0) scoreDiff--; /* F loses to W */
                    } else if (s[i] == 'E') {
                        if (move == 0) scoreDiff++; /* F beats E */
                        else if (move == 1) scoreDiff--; /* W loses to E */
                    }
                    dp[i + 1][scoreDiff][move] = (dp[i + 1][scoreDiff][move] + dp[i][j][last]) % MOD;
                }
            }
        }
    }
    /* Sum all ways where Bob's score is greater than Alice's (scoreDiff > n) */
    int result = 0;
    for (int j = n + 1; j <= 2 * n; j++) {
        for (int last = 0; last < 3; last++) {
            result = (result + dp[n][j][last]) % MOD;
        }
    }
    return result;
    
}
