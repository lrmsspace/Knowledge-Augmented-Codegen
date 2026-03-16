// Source: https://leetcode.com/problems/nim-game/   |   Difficulty: Easy
//
// Problem Description:
// You are playing the following Nim Game with your friend:
//
//
// 	Initially, there is a heap of stones on the table.
// 	You and your friend will alternate taking turns, and you go first.
// 	On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
// 	The one who removes the last stone is the winner.
//
//
// Given n, the number of stones in the heap, return true if you can win the game assuming both you and your friend play optimally, otherwise return false.
//
// Example:
// Input: n = 4
// Output: false
// Explanation: These are the possible outcomes:
// 1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
// 2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
// 3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
// In all outcomes, your friend wins.
//
// Constraints:
// 1 <= n <= 231 - 1
//
// Helpful references (internal KB):
// - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
//   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
//   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
//   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
//   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
// - Sprague-Grundy theorem. Nim (graph, number, game-theory, recursion, prefix-xor)
//   • When to use: Use to determine winning and losing positions in any finite impartial game under normal play. It allows reducing complex games to an equivalent Nim pile, simplifying analysis.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under normal play is equivalent to a Nim pile of a certain size, called its Grundy value or nim-value. This value is computed recursively as the minimum excludant (mex) of the Grundy values of all states reachable in one move, typically with memoization for efficiency.
//   • Invariants: For any state, all its successor states' Grundy values are computed or will be computed before its own.; The mex function always returns the smallest non-negative integer not found in its input set.
//   • Tips: Memoize Grundy values for each game state to avoid redundant computations.; Ensure all possible moves from a given state are correctly identified.
//   • Pitfalls: Applying the theorem to non-impartial games or games not under normal play.; Incorrectly calculating the mex function or missing reachable states.
// - Sprague-Grundy theorem. Nim (graph, number, game-theory, recursion)
//   • When to use: Use to analyze impartial games under normal play convention, determining winning/losing positions and optimal strategies. It applies when a game can be decomposed into independent subgames.
//   • Idea: The Sprague-Grundy theorem states that every impartial game is equivalent to a Nim pile of a certain size (its nim-value or Grundy number). This allows complex games to be analyzed by XORing their individual game states, typically with polynomial time complexity for Grundy number calculation.
//   • Invariants: The Nim-sum of a losing position is always zero.; From any winning position, there exists a move to a losing position.
//   • Tips: Understand the concept of Nim-sum (XOR sum) for game states.; Calculate Grundy numbers (nim-values) for subgames using the mex (minimum excluded value) rule.
//   • Pitfalls: Applying to non-impartial games or games not under normal play convention.; Incorrectly calculating mex values or Nim-sums.
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
var canWinNim = function(n) {
    // In Nim, if the number of stones is a multiple of 4, the first player will always lose if the opponent plays optimally.
    // This is because the opponent can always take enough stones to leave a multiple of 4 for the first player on their next turn.
    return n % 4 !== 0;
};
