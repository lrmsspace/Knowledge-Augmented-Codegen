// Source: https://leetcode.com/problems/number-of-strings-which-can-be-rearranged-to-contain-substring/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n.
//
// A string s is called good if it contains only lowercase English characters and it is possible to rearrange the characters of s such that the new string contains "leet" as a substring.
//
// For example:
//
//
// 	The string "lteer" is good because we can rearrange it to form "leetr" .
// 	"letl" is not good because we cannot rearrange it to contain "leet" as a substring.
//
//
// Return the total number of good strings of length n.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: n = 4
// Output: 12
// Explanation: The 12 strings which can be rearranged to have "leet" as a substring are: "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
//
// Constraints:
// 1 <= n <= 105
//
// Helpful references (internal KB):
// - Binary Exponentiation (number, mod-exp, divide-and-conquer)
//   • When to use: Use when calculating a^n efficiently, especially for large n or when results need to be taken modulo some number. It reduces the number of multiplications from linear to logarithmic.
//   • Idea: Binary exponentiation computes a^n by repeatedly squaring the base and multiplying terms corresponding to the set bits in the exponent's binary representation. This method achieves a time complexity of O(log n) multiplications.
//   • Invariants: The product of `result` and `current_base` raised to the `remaining_exponent` equals the initial `a^N`.; `current_base` always represents `a` raised to the power of `2^k` for the current iteration `k`.
//   • Tips: Handle base cases like n=0 (result is 1) and n=1 (result is a).; Use long long or appropriate large integer types for intermediate products to prevent overflow.
//   • Pitfalls: Integer overflow if not using appropriate data types or modulo arithmetic.; Incorrectly handling negative exponents (typically not covered by basic binary exponentiation).
// - Binary Exponentiation (number, mod-exp, recursion)
//   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
//   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
//   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
//   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
//   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int stringCount(int n) {
    const int MOD = 1000000007;
    if (n < 4) {
        return 0; // Not enough characters to form "leet"
    }
    
    // Calculate the number of ways to arrange n characters with "leet" as a substring
    // We can treat "leet" as a single block, so we have (n - 4 + 1) blocks to arrange
    // The number of ways to arrange these blocks is (n - 3)! / (1! * (n - 4)!)
    
    long long factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial = (factorial * i) % MOD;
    }
    
    long long inverse_factorial_1 = 1; // Inverse of 1! is 1
    long long inverse_factorial_n_minus_4 = 1; // Inverse of (n - 4)!
    
    for (int i = 1; i <= n - 4; i++) {
        inverse_factorial_n_minus_4 = (inverse_factorial_n_minus_4 * i) % MOD;
    }
    
    // Calculate the modular inverse using Fermat's little theorem
    long long inverse_factorial_n_minus_4_mod = 1;
    int exponent = MOD - 2; // Since MOD is prime, we can use this exponent for the inverse
    long long base = inverse_factorial_n_minus_4;
    
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            inverse_factorial_n_minus_4_mod = (inverse_factorial_n_minus_4_mod * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent /= 2;
    }
    
    // Calculate the result using the formula: factorial / (1! * (n - 4)!)
    long long result = factorial;
    result = (result * inverse_factorial_1) % MOD; // Multiply by the inverse of 1!
    result = (result * inverse_factorial_n_minus_4_mod) % MOD; // Multiply by the inverse of (n - 4)!
    
    return result;      
}
