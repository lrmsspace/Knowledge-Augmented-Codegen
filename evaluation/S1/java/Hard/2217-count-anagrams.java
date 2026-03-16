// Source: https://leetcode.com/problems/count-anagrams/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s containing one or more words. Every consecutive pair of words is separated by a single space ' '.
//
// A string t is an anagram of string s if the ith word of t is a permutation of the ith word of s.
//
//
// 	For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc bef" are not.
//
//
// Return the number of distinct anagrams of s. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "too hot"
// Output: 18
// Explanation: Some of the anagrams of the given string are "too hot", "oot hot", "oto toh", "too toh", and "too oht".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters and spaces ' '.
// 	There is single space between consecutive words.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long modInverse(long a, int mod) {
        long result = 1;
        int exponent = mod - 2; // Using Fermat's Little Theorem
        while (exponent > 0) {
            if ((exponent & 1) == 1) {
                result = (result * a) % mod;
            }
            a = (a * a) % mod;
            exponent >>= 1;
        }
        return result;
    }
    public int countAnagrams(String s) {
        final int MOD = 1_000_000_007;
        String[] words = s.split(" ");
        int maxLen = 0;
        for (String word : words) {
            maxLen = Math.max(maxLen, word.length());
        }

        long[] fact = new long[maxLen + 1];
        long[] invFact = new long[maxLen + 1];
        fact[0] = 1;
        for (int i = 1; i <= maxLen; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
        invFact[maxLen] = modInverse(fact[maxLen], MOD);
        for (int i = maxLen - 1; i >= 0; i--) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
        }

        long result = 1;
        for (String word : words) {
            int[] charCount = new int[26];
            for (char c : word.toCharArray()) {
                charCount[c - 'a']++;
            }

            long numerator = fact[word.length()];
            long denominator = 1;
            for (int count : charCount) {
                if (count > 1) {
                    denominator = (denominator * fact[count]) % MOD;
                }
            }

            long ways = (numerator * modInverse(denominator, MOD)) % MOD;
            result = (result * ways) % MOD;
        }

        return (int) result;            
    }
}
