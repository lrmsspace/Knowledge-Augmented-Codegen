// Source: https://leetcode.com/problems/find-the-winning-player-in-coin-game/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers x and y, denoting the number of coins with values 75 and 10 respectively.
//
// Alice and Bob are playing a game. Each turn, starting with Alice, the player must pick up coins with a total value 115. If the player is unable to do so, they lose the game.
//
// Return the name of the player who wins the game if both players play optimally.
//
// Example:
// Input: x = 2, y = 7
//
// Output: "Alice"
//
// Explanation:
//
// The game ends in a single turn:
//
//
// 	Alice picks 1 coin with a value of 75 and 4 coins with a value of 10.
//
// Constraints:
// 1 <= x, y <= 100
//
// Helpful references (internal KB):
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Gray code (number, simulation)
//   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
//   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
//   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
//   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
//   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* winningPlayer(int x, int y) {
    // The total value of coins needed to win is 115.
    // We can use at most x coins of value 75 and y coins of value 10.
    // We need to check if Alice can pick coins worth 115 in her first turn.
    
    // Calculate the maximum number of 75-value coins Alice can use without exceeding 115.
    int max_75_coins = (115 < 75 * x) ? (115 / 75) : x;
    
    // Check if Alice can make the total of 115 using max_75_coins and the remaining value with 10-value coins.
    for (int i = max_75_coins; i >= 0; i--) {
        int remaining_value = 115 - (i * 75);
        if (remaining_value <= y * 10) {
            return "Alice";
        }
    }
    
    // If Alice cannot make the total of 115, Bob wins.
    return "Bob";       
}
