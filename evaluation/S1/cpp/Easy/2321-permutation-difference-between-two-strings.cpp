// Source: https://leetcode.com/problems/permutation-difference-between-two-strings/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings s and t such that every character occurs at most once in s and t is a permutation of s.
//
// The permutation difference between s and t is defined as the sum of the absolute difference between the index of the occurrence of each character in s and the index of the occurrence of the same character in t.
//
// Return the permutation difference between s and t.
//
// Example:
// Input: s = "abc", t = "bac"
//
// Output: 2
//
// Explanation:
//
// For s = "abc" and t = "bac", the permutation difference of s and t is equal to the sum of:
//
//
// 	The absolute difference between the index of the occurrence of "a" in s and the index of the occurrence of "a" in t.
// 	The absolute difference between the index of the occurrence of "b" in s and the index of the occurrence of "b" in t.
// 	The absolute difference between the index of the occurrence of "c" in s and the index of the occurrence of "c" in t.
//
//
// That is, the permutation difference between s and t is equal to |0 - 1| + |1 - 0| + |2 - 2| = 2.
//
// Constraints:
// 1 <= s.length <= 26
// 	Each character occurs at most once in s.
// 	t is a permutation of s.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
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
    int findPermutationDifference(string s, string t) {
        int indexS[26] = {0};
        int indexT[26] = {0};
        
        for (int i = 0; i < s.length(); i++) {
            indexS[s[i] - 'a'] = i;
        }
        
        for (int i = 0; i < t.length(); i++) {
            indexT[t[i] - 'a'] = i;
        }
        
        int difference = 0;
        for (int i = 0; i < 26; i++) {
            if (indexS[i] != 0 || indexT[i] != 0) { // character exists in s and t
                difference += abs(indexS[i] - indexT[i]);
            }
        }
        
        return difference;          
    }
};
