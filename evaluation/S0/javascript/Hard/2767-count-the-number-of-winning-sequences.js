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

/**
 * @param {string} s
 * @return {number}
 */
var countWinningSequences = function(s) {
    const MOD = 1e9 + 7;
    const n = s.length;
    const dp = Array.from({ length: n + 1 }, () => Array(3).fill(0).map(() => Array(2 * n + 1).fill(0)));
    const charToIndex = { 'F': 0, 'W': 1, 'E': 2 };
    dp[0][0][n] = 1;
    dp[0][1][n] = 1;
    dp[0][2][n] = 1;
    for (let i = 1; i <= n; i++) {
        const aliceMove = charToIndex[s[i - 1]];
        for (let bobMove = 0; bobMove < 3; bobMove++) {
            for (let scoreDiff = 0; scoreDiff <= 2 * n; scoreDiff++) {
                for (let prevBobMove = 0; prevBobMove < 3; prevBobMove++) {
                    if (bobMove === prevBobMove) continue;
                    let newScoreDiff = scoreDiff;
                    if ((bobMove === 0 && aliceMove === 2) || (bobMove === 1 && aliceMove === 0) || (bobMove === 2 && aliceMove === 1)) {
                        newScoreDiff++;
                    } else if ((aliceMove === 0 && bobMove === 2) || (aliceMove === 1 && bobMove === 0) || (aliceMove === 2 && bobMove === 1)) {
                        newScoreDiff--;
                    }
                    if (newScoreDiff >= 0 && newScoreDiff <= 2 * n) {
                        dp[i][bobMove][newScoreDiff]
                            = (dp[i][bobMove][newScoreDiff] + dp[i - 1][prevBobMove][scoreDiff]) % MOD;
                    }
                }
            }
        }
    }       
    let result = 0;
    for (let bobMove = 0; bobMove < 3; bobMove++) {
        for (let scoreDiff = n + 1; scoreDiff <= 2 * n; scoreDiff++) {
            result = (result + dp[n][bobMove][scoreDiff]) % MOD;
        }
    }
    return result;
};
