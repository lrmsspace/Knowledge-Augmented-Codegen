// Source: https://leetcode.com/problems/can-i-win/   |   Difficulty: Medium
//
// Problem Description:
// In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.
//
// What if we change the game so that players cannot re-use integers?
//
// For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.
//
// Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise, return false. Assume both players play optimally.
//
// Example:
// Input: maxChoosableInteger = 10, desiredTotal = 11
// Output: false
// Explanation:
// No matter which integer the first player choose, the first player will lose.
// The first player can choose an integer from 1 up to 10.
// If the first player choose 1, the second player can only choose integers from 2 up to 10.
// The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
// Same with other integers chosen by the first player, the second player will always win.
//
// Constraints:
// 1 <= maxChoosableInteger <= 20
// 	0 <= desiredTotal <= 300
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
 * @param {number} maxChoosableInteger
 * @param {number} desiredTotal
 * @return {boolean}
 */
var canIWin = function(maxChoosableInteger, desiredTotal) {
    if (desiredTotal <= 0) return true;
    const sum = (maxChoosableInteger * (maxChoosableInteger + 1)) / 2;
    if (sum < desiredTotal) return false;
    
    const memo = new Map();
    function canWin(used, total) {
        if (memo.has(used)) return memo.get(used);
        for (let i = 1; i <= maxChoosableInteger; i++) {
            if ((used & (1 << i)) === 0) {
                if (total + i >= desiredTotal) {
                    memo.set(used, true);
                    return true;
                }
                if (!canWin(used | (1 << i), total + i)) {
                    memo.set(used, true);
                    return true;
                }
            }
        }
        memo.set(used, false);
        return false;
    }

    return canWin(0, 0);
};
