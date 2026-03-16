// Source: https://leetcode.com/problems/number-of-distinct-roll-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. You roll a fair 6-sided dice n times. Determine the total number of distinct sequences of rolls possible such that the following conditions are satisfied:
//
//
// 	The greatest common divisor of any adjacent values in the sequence is equal to 1.
// 	There is at least a gap of 2 rolls between equal valued rolls. More formally, if the value of the ith roll is equal to the value of the jth roll, then abs(i - j) > 2.
//
//
// Return the total number of distinct sequences possible. Since the answer may be very large, return it modulo 109 + 7.
//
// Two sequences are considered distinct if at least one element is different.
//
// Example:
// Input: n = 4
// Output: 184
// Explanation: Some of the possible sequences are (1, 2, 3, 4), (6, 1, 2, 3), (1, 2, 3, 1), etc.
// Some invalid sequences are (1, 2, 1, 3), (1, 2, 3, 6).
// (1, 2, 1, 3) is invalid since the first and third roll have an equal value and abs(1 - 3) = 2 (i and j are 1-indexed).
// (1, 2, 3, 6) is invalid since the greatest common divisor of 3 and 6 = 3.
// There are a total of 184 distinct sequences possible, so we return 184.
//
// Constraints:
// 1 <= n <= 104
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
// - Binary Exponentiation by Factoring (number, mod-exp)
//   • When to use: Use when computing modular exponentiation $ax^y \pmod{2^d}$ where the modulus is a power of two ($2^d$ with $d \geq 3$) and the base $x$ is odd. It leverages the specific structure of the multiplicative group modulo $2^d$ for efficient calculation.
//   • Idea: This algorithm computes $ax^y \pmod{2^d}$ for odd $x$ by transforming the problem using a 'logarithm' $L(x)$ and a fixed base $b \equiv 5 \pmod 8$. It achieves $O(d)$ complexity for the exponentiation and logarithm parts, plus a single multiplication by $y$.
//   • Invariants: The intermediate result is always congruent to the original expression modulo $2^d$.; The base used for exponentiation is always odd and congruent to $1 \pmod 4$ (after potential transformation).
//   • Tips: Handle $x \equiv 3 \pmod 4$ by transforming $x \mapsto -x$ and $a \mapsto (-1)^y a$.; The modulus $2^d$ must have $d \geq 3$ for the group structure to apply.
//   • Pitfalls: Incorrectly handling the $x \equiv 3 \pmod 4$ case or its sign implications.; Applying the method to even bases $x$, which breaks the underlying group structure.
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int distinctSequences(int n) {
    if (n == 1) {
        return 6;
    }
    if (n == 2) {
        return 30;
    }
    if (n == 3) {
        return 150;
    }

    int mod = 1000000007;
    long dp[n][7];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            dp[i][j] = 0;
        }
    }

    for (int j = 1; j <= 6; j++) {
        dp[0][j] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= 6; j++) {
            for (int k = 1; k <= 6; k++) {
                if (j != k && __gcd(j, k) == 1) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
                }
            }
        }
    }

    long result = 0;
    for (int j = 1; j <= 6; j++) {
        result = (result + dp[n - 1][j]) % mod;
    }

    return result;      
}
