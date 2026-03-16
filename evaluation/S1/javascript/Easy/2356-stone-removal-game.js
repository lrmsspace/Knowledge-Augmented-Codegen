// Source: https://leetcode.com/problems/stone-removal-game/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are playing a game where they take turns removing stones from a pile, with Alice going first.
//
//
// 	Alice starts by removing exactly 10 stones on her first turn.
// 	For each subsequent turn, each player removes exactly 1 fewer stone than the previous opponent.
//
//
// The player who cannot make a move loses the game.
//
// Given a positive integer n, return true if Alice wins the game and false otherwise.
//
// Example:
// Input: n = 12
//
// Output: true
//
// Explanation:
//
//
// 	Alice removes 10 stones on her first turn, leaving 2 stones for Bob.
// 	Bob cannot remove 9 stones, so Alice wins.
//
// Constraints:
// 1 <= n <= 50
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
 * @param {number} n
 * @return {boolean}
 */
var canAliceWin = function(n) {
    let stones = n;     
    let remove = 10;    
    while (stones > 0) {
        stones -= remove;
        if (stones < 0) {
            return false;  
        }
        remove = Math.max(remove - 1, 1);
    }
    return true;    
};
