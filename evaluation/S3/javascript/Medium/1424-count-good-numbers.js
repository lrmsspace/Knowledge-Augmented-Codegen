// Source: https://leetcode.com/problems/count-good-numbers/   |   Difficulty: Medium
//
// Problem Description:
// A digit string is good if the digits (0-indexed) at even indices are even and the digits at odd indices are prime (2, 3, 5, or 7).
//
//
// 	For example, "2582" is good because the digits (2 and 8) at even positions are even and the digits (5 and 2) at odd positions are prime. However, "3245" is not good because 3 is at an even index but is not even.
//
//
// Given an integer n, return the total number of good digit strings of length n. Since the answer may be large, return it modulo 109 + 7.
//
// A digit string is a string consisting of digits 0 through 9 that may contain leading zeros.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The good numbers of length 1 are "0", "2", "4", "6", "8".
//
// Constraints:
// 1 <= n <= 1015
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
// - Fibonacci Numbers (number, recursion, binary-lifting)
//   • When to use: Use when computing the N-th Fibonacci number for extremely large N, or when the result needs to be calculated modulo a specific value, requiring logarithmic time complexity.
//   • Idea: This method computes the N-th Fibonacci number by leveraging matrix exponentiation or specific doubling identities, reducing the problem size by half in each step. It achieves an O(log N) time complexity.
//   • Invariants: The function `compute(n)` always returns the pair `(F_n, F_{n+1})`.; For any `k`, the values `F_k` and `F_{k+1}` are correctly computed before deriving `F_{2k}` and `F_{2k+1}`.
//   • Tips: Utilize matrix exponentiation for a general and robust approach.; The doubling identities F_2k+1 and F_2k can be faster than explicit matrix multiplication.
//   • Pitfalls: Integer overflow if modulo arithmetic or arbitrary-precision integers are not used for large N.; Incorrectly defining base cases in the recursive implementation can lead to errors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {number}
 */
var countGoodNumbers = function(n) {
    const MOD = 1000000007;
    const evenCount = Math.ceil(n / 2);
    const oddCount = Math.floor(n / 2);
    
    // There are 5 choices for even indices (0, 2, 4, 6, 8) and 4 choices for odd indices (2, 3, 5, 7)
    const result = (modPow(5, evenCount, MOD) * modPow(4, oddCount, MOD)) % MOD;
    
    return result;
};
