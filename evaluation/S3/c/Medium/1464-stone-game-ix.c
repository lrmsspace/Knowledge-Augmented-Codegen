// Source: https://leetcode.com/problems/stone-game-ix/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob continue their games with stones. There is a row of n stones, and each stone has an associated value. You are given an integer array stones, where stones[i] is the value of the ith stone.
//
// Alice and Bob take turns, with Alice starting first. On each turn, the player may remove any stone from stones. The player who removes a stone loses if the sum of the values of all removed stones is divisible by 3. Bob will win automatically if there are no remaining stones (even if it is Alice's turn).
//
// Assuming both players play optimally, return true if Alice wins and false if Bob wins.
//
// Example:
// Input: stones = [2,1]
// Output: true
// Explanation: The game will be played as follows:
// - Turn 1: Alice can remove either stone.
// - Turn 2: Bob removes the remaining stone. 
// The sum of the removed stones is 1 + 2 = 3 and is divisible by 3. Therefore, Bob loses and Alice wins the game.
//
// Constraints:
// 1 <= stones.length <= 105
// 	1 <= stones[i] <= 104
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool stoneGameIX(int* stones, int stonesSize) {
    int count[3] = {0};
    for (int i = 0; i < stonesSize; ++i) {
        count[stones[i] % 3]++;
    }
    
    if (count[0] % 2 == 0) {
        return abs(count[1] - count[2]) > 2;
    } else {
        return abs(count[1] - count[2]) <= 2;
    }       
}
