// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s (0-indexed)​​​​​​. You are asked to perform the following operation on s​​​​​​ until you get a sorted string:
//
//
// 	Find the largest index i such that 1 <= i < s.length and s[i] < s[i - 1].
// 	Find the largest index j such that i <= j < s.length and s[k] < s[i - 1] for all the possible values of k in the range [i, j] inclusive.
// 	Swap the two characters at indices i - 1​​​​ and j​​​​​.
// 	Reverse the suffix starting at index i​​​​​​.
//
//
// Return the number of operations needed to make the string sorted. Since the answer can be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "cba"
// Output: 5
// Explanation: The simulation goes as follows:
// Operation 1: i=2, j=2. Swap s[1] and s[2] to get s="cab", then reverse the suffix starting at 2. Now, s="cab".
// Operation 2: i=1, j=2. Swap s[0] and s[2] to get s="bac", then reverse the suffix starting at 1. Now, s="bca".
// Operation 3: i=2, j=2. Swap s[1] and s[2] to get s="bac", then reverse the suffix starting at 2. Now, s="bac".
// Operation 4: i=1, j=1. Swap s[0] and s[1] to get s="abc", then reverse the suffix starting at 1. Now, s="acb".
// Operation 5: i=2, j=2. Swap s[1] and s[2] to get s="abc", then reverse the suffix starting at 2. Now, s="abc".
//
// Constraints:
// 1 <= s.length <= 3000
// 	s​​​​​​ consists only of lowercase English letters.
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
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var makeStringSorted = function(s) {
    const mod = 1e9 + 7;
    const n = s.length;
    const fact = new Array(n + 1).fill(1);
    const invFact = new Array(n + 1).fill(1);

    for (let i = 2; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }

    invFact[n] = modExp(fact[n], mod - 2, mod);
    for (let i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }

    const freq = new Array(26).fill(0);
    for (const char of s) {
        freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }

    let operations = 0;

    for (let i = 0; i < n; i++) {
        const charIndex = s.charCodeAt(i) - 'a'.charCodeAt(0);
        let lessCount = 0;

        for (let j = 0; j < charIndex; j++) {
            if (freq[j] > 0) {
                lessCount += freq[j];
            }
        }

        if (lessCount > 0) {
            operations += (lessCount * fact[n - i - 1]) % mod;
            operations %= mod;

            for (let k = 0; k < 26; k++) {
                if (freq[k] > 0) {
                    operations *= invFact[freq[k]];
                    operations %= mod;
                }
            }
        }

        freq[charIndex]--;
    }

    return operations;

    function modExp(base, exp, m) {
        let result = 1;
        base %= m;

        while (exp > 0) {
            if (exp % 2 === 1) {
                result = (result * base) % m;
            }
            base = (base * base) % m;
            exp >>= 1;
        }

        return result;
    }
};
