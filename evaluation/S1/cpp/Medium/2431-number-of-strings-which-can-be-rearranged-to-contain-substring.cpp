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
// - Binary Exponentiation by Factoring (number, mod-exp)
//   • When to use: When computing a number raised to a very large power modulo another number efficiently. It is also applicable when specific properties of the base or modulus allow for specialized bitwise optimizations.
//   • Idea: Binary exponentiation (also known as exponentiation by squaring) computes a^b mod m by leveraging the binary representation of the exponent b. This method significantly reduces the number of multiplications from O(b) to O(log b), achieving O(log b) time complexity.
//   • Invariants: (original_base^original_exponent) % m == (current_base^current_exponent * accumulated_result) % m; current_exponent is always non-negative and strictly decreases towards zero.
//   • Tips: Use long long for intermediate products to prevent overflow before taking modulo.; Apply the modulo operation after each multiplication to keep numbers small.
//   • Pitfalls: Integer overflow if intermediate products are not reduced modulo m frequently enough.; Incorrectly handling the exponent 0 or negative exponents (if applicable).
// - Chinese Remainder Theorem (number, mod-exp)
//   • When to use: Used to find an integer that satisfies a system of multiple congruence relations, particularly when the moduli are pairwise coprime. It's essential for reconstructing numbers from their remainders.
//   • Idea: The Chinese Remainder Theorem finds a unique integer solution to a system of linear congruences, modulo the product of their pairwise coprime moduli. It iteratively combines congruences, often using the Extended Euclidean Algorithm for modular inverses, with a complexity polynomial in the number of congruences.
//   • Invariants: The current combined solution satisfies all previously processed congruences.; The current combined modulus is the product of all previously processed pairwise coprime moduli.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime, leading to no unique solution or no solution.; Incorrectly calculating modular inverses, which is crucial for the algorithm.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int stringCount(int n) {
        const int MOD = 1000000007;
        if (n < 4) return 0;
        // Total strings of length n: 26^n
        // Strings that cannot form "leet":
        // Case 1: No 'l', 'e', or 't': 23^n
        // Case 2: At least one 'l', no 'e' or 't': 24^n - 23^n
        // Case 3: At least one 'e', no 'l' or 't': 24^n - 23^n
        // Case 4: At least one 't', no 'l' or 'e': 24^n - 23^n
        // Case 5: At least one 'l' and one 'e', no 't': 25^n - 2*24^n + 23^n
        // Case 6: At least one 'l' and one 't', no 'e': 25^n - 2*24^n + 23^n
        // Case 7: At least one 'e' and one 't', no 'l': 25^n - 2*24^n + 23^n
        // Total invalid = Case1 + Case2 + Case3 + Case4 + Case5 + Case6 + Case7
        // = 23^n + 3*(24^n - 23^n) + 3*(25^n - 2*24^n + 23^n)
        // = 3*25^n - 3*24^n + 1*23^n
        long long total = modExp(26, n, MOD);
        long long invalid = (3 * modExp(25, n, MOD) % MOD - 3 * modExp(24, n, MOD) % MOD + modExp(23, n, MOD) % MOD + MOD) % MOD;
        return (total - invalid + MOD) % MOD;           
    }
};
