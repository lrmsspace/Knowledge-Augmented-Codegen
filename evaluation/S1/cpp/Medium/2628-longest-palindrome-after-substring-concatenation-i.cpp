// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 30
// 	s and t consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestPalindrome(string s, string t) {
        int n = s.size();
        int m = t.size();

        auto manacher = [](const string& str) {
            int len = str.size();
            vector<int> d_odd(len, 0);
            int l = 0, r = -1;
            for (int i = 0; i < len; ++i) {
                int k = (i > r) ? 1 : min(d_odd[l + r - i], r - i + 1);
                while (0 <= i - k && i + k < len && str[i - k] == str[i + k]) {
                    ++k;
                }
                d_odd[i] = k--;
                if (i + k > r) {
                    l = i - k;
                    r = i + k;
                }
            }
            return d_odd;
        };

        vector<int> d_s = manacher(s);
        vector<int> d_t = manacher(t);

        int max_len = 0;

        for (int i = 0; i < n; ++i) {
            int radius = d_s[i];
            int pal_len = 2 * radius - 1;
            if (pal_len > max_len) {
                max_len = pal_len;
            }
        }

        for (int i = 0; i < m; ++i) {
            int radius = d_t[i];
            int pal_len = 2 * radius - 1;
            if (pal_len > max_len) {
                max_len = pal_len;
            }
        }

        for (int i = 0; i < n; ++i) {
            int radius_s = d_s[i];
            for (int j = 0; j < m; ++j) {
                int radius_t = d_t[j];
                int common_radius = min(radius_s, radius_t);
                int pal_len = 2 * common_radius - 1;
                if (pal_len > max_len) {
                    max_len = pal_len;
                }
            }
        }

        return max_len;         
    }
};
