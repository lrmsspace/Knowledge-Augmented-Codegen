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
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countAnagrams(string s) {
        const int MOD = 1e9 + 7;
        vector<long long> fact(100001, 1);
        for (int i = 2; i <= 100000; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        long long result = 1;
        istringstream iss(s);
        string word;
        while (iss >> word) {
            vector<int> freq(26, 0);
            for (char c : word) {
                freq[c - 'a']++;
            }
            long long permutations = fact[word.size()];
            for (int count : freq) {
                if (count > 1) {
                    permutations = (permutations * modInverse(fact[count], MOD)) % MOD;
                }
            }
            result = (result * permutations) % MOD;
        }
        return result;          
    }
};
