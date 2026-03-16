// Source: https://leetcode.com/problems/check-if-the-number-is-fascinating/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n that consists of exactly 3 digits.
//
// We call the number n fascinating if, after the following modification, the resulting number contains all the digits from 1 to 9 exactly once and does not contain any 0's:
//
//
// 	Concatenate n with the numbers 2 * n and 3 * n.
//
//
// Return true if n is fascinating, or false otherwise.
//
// Concatenating two numbers means joining them together. For example, the concatenation of 121 and 371 is 121371.
//
// Example:
// Input: n = 192
// Output: true
// Explanation: We concatenate the numbers n = 192 and 2 * n = 384 and 3 * n = 576. The resulting number is 192384576. This number contains all the digits from 1 to 9 exactly once.
//
// Constraints:
// 100 <= n <= 999
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Rabin-Karp Algorithm for string matching (string, number, hashing, rolling-hash)
//   • When to use: To efficiently find all occurrences of a given pattern string within a larger text string, especially when multiple patterns might be searched or for average-case linear time performance.
//   • Idea: The Rabin-Karp algorithm finds occurrences of a pattern in a text by comparing their hash values, using a rolling hash function to efficiently update substring hashes. It achieves an average time complexity of O(|s| + |t|) and a worst-case of O(|s| * |t|).
//   • Invariants: The hash of the pattern string remains constant throughout the search.; The current window's hash value accurately represents the substring T[i...i+len(P)-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Select a suitable base (e.g., a prime greater than alphabet size) for polynomial hashing.
//   • Pitfalls: Hash collisions can lead to false positives and degrade worst-case performance to O(MN).; Poor choice of base or modulus can significantly increase collision frequency.
// - Integer factorization (number, enumeration)
//   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
//   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
//   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
//   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
//   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isFascinating(int n) {
        StringBuilder sb = new StringBuilder();
        sb.append(n);
        sb.append(2 * n);
        sb.append(3 * n);

        String concatenated = sb.toString();
        if (concatenated.contains("0") || concatenated.length() != 9) {
            return false;
        }

        boolean[] seenDigits = new boolean[10]; // Index 0-9 for digits
        for (char digit : concatenated.toCharArray()) {
            int d = digit - '0';
            if (seenDigits[d]) {
                return false; // Digit already seen, not fascinating
            }
            seenDigits[d] = true;
        }

        // Check if all digits from 1 to 9 are seen
        for (int i = 1; i <= 9; i++) {
            if (!seenDigits[i]) {
                return false; // Missing a digit, not fascinating
            }
        }

        return true; // All digits from 1 to 9 are present exactly once         
    }
}
