// Source: https://leetcode.com/problems/check-if-an-original-string-exists-given-two-encoded-strings/   |   Difficulty: Hard
//
// Problem Description:
// An original string, consisting of lowercase English letters, can be encoded by the following steps:
//
//
// 	Arbitrarily split it into a sequence of some number of non-empty substrings.
// 	Arbitrarily choose some elements (possibly none) of the sequence, and replace each with its length (as a numeric string).
// 	Concatenate the sequence as the encoded string.
//
//
// For example, one way to encode an original string "abcdefghijklmnop" might be:
//
//
// 	Split it as a sequence: ["ab", "cdefghijklmn", "o", "p"].
// 	Choose the second and third elements to be replaced by their lengths, respectively. The sequence becomes ["ab", "12", "1", "p"].
// 	Concatenate the elements of the sequence to get the encoded string: "ab121p".
//
//
// Given two encoded strings s1 and s2, consisting of lowercase English letters and digits 1-9 (inclusive), return true if there exists an original string that could be encoded as both s1 and s2. Otherwise, return false.
//
// Note: The test cases are generated such that the number of consecutive digits in s1 and s2 does not exceed 3.
//
// Example:
// Input: s1 = "internationalization", s2 = "i18n"
// Output: true
// Explanation: It is possible that "internationalization" was the original string.
// - "internationalization" 
//   -> Split:       ["internationalization"]
//   -> Do not replace any element
//   -> Concatenate:  "internationalization", which is s1.
// - "internationalization"
//   -> Split:       ["i", "nternationalizatio", "n"]
//   -> Replace:     ["i", "18",                 "n"]
//   -> Concatenate:  "i18n", which is s2
//
// Constraints:
// 1 <= s1.length, s2.length <= 40
// 	s1 and s2 consist of digits 1-9 (inclusive), and lowercase English letters only.
// 	The number of consecutive digits in s1 and s2 does not exceed 3.
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - String Hashing (string, number, hashing)
//   • When to use: When comparing strings or substrings efficiently, especially for equality checks or finding duplicates, to reduce comparison time from O(m) to O(1) on average.
//   • Idea: String hashing converts a string into a numerical value (hash) using a polynomial rolling hash function, allowing for O(1) average-case comparison of strings or substrings. This technique typically involves modular arithmetic to keep hash values within a manageable range.
//   • Invariants: The hash of any prefix s[0...i] is correctly calculated based on the chosen base and modulus.; Precomputed powers of the base 'p' are available and correct for all required string lengths.
//   • Tips: Convert characters to integers starting from 1 (e.g., 'a' -> 1) to avoid zero hashes for strings like 'a', 'aa'.; Precompute powers of the base 'p' and their modular inverses for efficient rolling hash calculations.
//   • Pitfalls: Choosing 'a' -> 0 can lead to identical hashes for strings like 'a', 'aa', 'aaa', causing false positives.; Using a single hash function can lead to collisions, where different strings produce the same hash, requiring careful handling.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool possiblyEquals(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        unordered_map<string, bool> memo;

        function<bool(int, int, int)> dfs = [&](int i, int j, int diff) {
            if (i == n1 && j == n2) {
                return diff == 0;
            }
            string key = to_string(i) + "," + to_string(j) + "," + to_string(diff);
            if (memo.count(key)) {
                return memo[key];
            }

            if (diff == 0) {
                if (i < n1 && isalpha(s1[i]) && j < n2 && isalpha(s2[j])) {
                    if (s1[i] == s2[j]) {
                        return memo[key] = dfs(i + 1, j + 1, 0);
                    } else {
                        return memo[key] = false;
                    }
                }
                if (i < n1 && isdigit(s1[i])) {
                    int val = 0;
                    for (int k = i; k < n1 && isdigit(s1[k]); ++k) {
                        val = val * 10 + (s1[k] - '0');
                        if (dfs(k + 1, j, diff + val)) {
                            return memo[key] = true;
                        }
                    }
                }
                if (j < n2 && isdigit(s2[j])) {
                    int val = 0;
                    for (int k = j; k < n2 && isdigit(s2[k]); ++k) {
                        val = val * 10 + (s2[k] - '0');
                        if (dfs(i, k + 1, diff - val)) {
                            return memo[key] = true;
                        }
                    }
                }
            } else if (diff > 0) {
                if (j < n2 && isalpha(s2[j])) {
                    return memo[key] = dfs(i, j + 1, diff - 1);
                }
                if (j < n2 && isdigit(s2[j])) {
                    int val = 0;
                    for (int k = j; k < n2 && isdigit(s2[k]); ++k) {
                        val = val * 10 + (s2[k] - '0');
                        if (dfs(i, k + 1, diff - val)) {
                            return memo[key] = true;
                        }
                    }
                }
            } else { // diff < 0
                if (i < n1 && isalpha(s1[i])) {
                    return memo[key] = dfs(i + 1, j, diff + 1);
                }
                if (i < n1 && isdigit(s1[i])) {
                    int val = 0;
                    for (int k = i; k < n1 && isdigit(s1[k]); ++k) {
                        val = val * 10 + (s1[k] - '0');
                        if (dfs(k + 1, j, diff + val)) {
                            return memo[key] = true;
                        }
                    }
                }
            }
            return memo[key] = false;
        }
        return dfs(0, 0, 0);
    }
};
