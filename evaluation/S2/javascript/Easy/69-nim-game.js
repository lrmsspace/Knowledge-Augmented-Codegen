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
// - Sprague-Grundy theorem. Nim (graph, number, game-theory, recursion, prefix-xor)
//   • When to use: Use to determine winning and losing positions in any finite impartial game under normal play. It allows reducing complex games to an equivalent Nim pile, simplifying analysis.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under normal play is equivalent to a Nim pile of a certain size, called its Grundy value or nim-value. This value is computed recursively as the minimum excludant (mex) of the Grundy values of all states reachable in one move, typically with memoization for efficiency.
//   • Invariants: For any state, all its successor states' Grundy values are computed or will be computed before its own.; The mex function always returns the smallest non-negative integer not found in its input set.
//   • Tips: Memoize Grundy values for each game state to avoid redundant computations.; Ensure all possible moves from a given state are correctly identified.
//   • Pitfalls: Applying the theorem to non-impartial games or games not under normal play.; Incorrectly calculating the mex function or missing reachable states.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Binary Exponentiation by Factoring (number, mod-exp)
//   • When to use: Use when computing modular exponentiation $ax^y \pmod{2^d}$ where the modulus is a power of two ($2^d$ with $d \geq 3$) and the base $x$ is odd. It leverages the specific structure of the multiplicative group modulo $2^d$ for efficient calculation.
//   • Idea: This algorithm computes $ax^y \pmod{2^d}$ for odd $x$ by transforming the problem using a 'logarithm' $L(x)$ and a fixed base $b \equiv 5 \pmod 8$. It achieves $O(d)$ complexity for the exponentiation and logarithm parts, plus a single multiplication by $y$.
//   • Invariants: The intermediate result is always congruent to the original expression modulo $2^d$.; The base used for exponentiation is always odd and congruent to $1 \pmod 4$ (after potential transformation).
//   • Tips: Handle $x \equiv 3 \pmod 4$ by transforming $x \mapsto -x$ and $a \mapsto (-1)^y a$.; The modulus $2^d$ must have $d \geq 3$ for the group structure to apply.
//   • Pitfalls: Incorrectly handling the $x \equiv 3 \pmod 4$ case or its sign implications.; Applying the method to even bases $x$, which breaks the underlying group structure.
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
    return n % 4 !== 0; 
};
