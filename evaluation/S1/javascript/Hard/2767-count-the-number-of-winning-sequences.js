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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var countWinningSequences = function(s) {
    const mod = 1e9 + 7;
    const n = s.length;
    const dp = Array.from({ length: n + 1 }, () => [0, 0, 0]);
    
    // Base case: At round 0, Bob can choose any of the three creatures
    dp[0] = [1, 1, 1]; // F, W, E respectively
    
    for (let i = 1; i <= n; i++) {
        const aliceMove = s[i - 1];
        
        for (let bobMove = 0; bobMove < 3; bobMove++) {
            // Bob cannot choose the same creature as in the previous round
            for (let prevBobMove = 0; prevBobMove < 3; prevBobMove++) {
                if (bobMove !== prevBobMove) {
                    // Calculate points awarded to Bob and Alice
                    let bobPoints = 0;
                    let alicePoints = 0;
                    
                    if ((bobMove === 0 && aliceMove === 'E') || 
                        (bobMove === 1 && aliceMove === 'F') || 
                        (bobMove === 2 && aliceMove === 'W')) {
                        bobPoints++;
                    } else if ((bobMove === 0 && aliceMove === 'F') || 
                               (bobMove === 1 && aliceMove === 'W') || 
                               (bobMove === 2 && aliceMove === 'E')) {
                        alicePoints++;
                    }
                    
                    dp[i][bobMove] = (dp[i][bobMove] + dp[i - 1][prevBobMove]) % mod;
                }
            }
        }
    }
    
    let totalWinningSequences = 0;
    
    for (let bobMove = 0; bobMove < 3; bobMove++) {
        totalWinningSequences = (totalWinningSequences + dp[n][bobMove]) % mod;
    }
    
    return totalWinningSequences;
};
