// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-score/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game with integers. You start with the integer 1 and you want to reach the integer target.
//
// In one move, you can either:
//
//
// 	Increment the current integer by one (i.e., x = x + 1).
// 	Double the current integer (i.e., x = 2 * x).
//
//
// You can use the increment operation any number of times, however, you can only use the double operation at most maxDoubles times.
//
// Given the two integers target and maxDoubles, return the minimum number of moves needed to reach target starting with 1.
//
// Example:
// Input: target = 5, maxDoubles = 0
// Output: 4
// Explanation: Keep incrementing by 1 until you reach target.
//
// Constraints:
// 1 <= target <= 109
// 	0 <= maxDoubles <= 100
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
 * @param {number} target
 * @param {number} maxDoubles
 * @return {number}
 */
var minMoves = function(target, maxDoubles) {
    let moves = 0;
    while (target > 1) {
        if (maxDoubles > 0 && target % 2 === 0) {
            target /= 2;
            maxDoubles--;
        } else {
            target -= 1;
        }
        moves++;
    }
    return moves;
};
