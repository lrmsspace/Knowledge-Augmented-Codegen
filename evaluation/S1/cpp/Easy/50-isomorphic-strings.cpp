// Source: https://leetcode.com/problems/isomorphic-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, determine if they are isomorphic.
//
// Two strings s and t are isomorphic if the characters in s can be replaced to get t.
//
// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
//
// Example:
// Input: s = "egg", t = "add"
//
// Output: true
//
// Explanation:
//
// The strings s and t can be made identical by:
//
//
// 	Mapping 'e' to 'a'.
// 	Mapping 'g' to 'd'.
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	t.length == s.length
// 	s and t consist of any valid ascii character.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
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
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) return false;

        unordered_map<char, char> s_to_t;
        unordered_map<char, char> t_to_s;

        for (size_t i = 0; i < s.length(); ++i) {
            char cs = s[i];
            char ct = t[i];

            // Check mapping from s to t
            if (s_to_t.find(cs) != s_to_t.end()) {
                if (s_to_t[cs] != ct) {
                    return false; // Inconsistent mapping
                }
            } else {
                s_to_t[cs] = ct;
            }

            // Check mapping from t to s
            if (t_to_s.find(ct) != t_to_s.end()) {
                if (t_to_s[ct] != cs) {
                    return false; // Inconsistent mapping
                }
            } else {
                t_to_s[ct] = cs;
            }
        }

        return true;            
    }
};
