// Source: https://leetcode.com/problems/count-number-of-texts/   |   Difficulty: Medium
//
// Problem Description:
// Alice is texting Bob using her phone. The mapping of digits to letters is shown in the figure below.
//
// In order to add a letter, Alice has to press the key of the corresponding digit i times, where i is the position of the letter in the key.
//
//
// 	For example, to add the letter 's', Alice has to press '7' four times. Similarly, to add the letter 'k', Alice has to press '5' twice.
// 	Note that the digits '0' and '1' do not map to any letters, so Alice does not use them.
//
//
// However, due to an error in transmission, Bob did not receive Alice's text message but received a string of pressed keys instead.
//
//
// 	For example, when Alice sent the message "bob", Bob received the string "2266622".
//
//
// Given a string pressedKeys representing the string received by Bob, return the total number of possible text messages Alice could have sent.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: pressedKeys = "22233"
// Output: 8
// Explanation:
// The possible text messages Alice could have sent are:
// "aaadd", "abdd", "badd", "cdd", "aaae", "abe", "bae", and "ce".
// Since there are 8 possible messages, we return 8.
//
// Constraints:
// 1 <= pressedKeys.length <= 105
// 	pressedKeys only consists of digits from '2' - '9'.
//
// Helpful references (internal KB):
// - Modular Multiplicative Inverse (array, number, dp-1d)
//   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
//   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
//   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
//   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
//   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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

int countTexts(char* pressedKeys) {
    int mod = 1e9 + 7;
    int n = strlen(pressedKeys);
    int dp[n + 1];
    dp[0] = 1; // Base case: there's one way to decode an empty string

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1]; // Single digit decoding

        // Check for two-digit decoding
        if (i > 1 && pressedKeys[i - 1] == pressedKeys[i - 2]) {
            dp[i] = (dp[i] + dp[i - 2]) % mod;
        }

        // Check for three-digit decoding (only for digits '7' and '9')
        if (i > 2 && pressedKeys[i - 1] == pressedKeys[i - 2] && pressedKeys[i - 2] == pressedKeys[i - 3]) {
            if (pressedKeys[i - 1] == '7' || pressedKeys[i - 1] == '9') {
                dp[i] = (dp[i] + dp[i - 3]) % mod;
            }
        }
    }

    return dp[n];       
}
