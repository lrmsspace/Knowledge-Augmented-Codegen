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
// - N/A
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
        int n = s.size();
        unordered_map<char, int> indexS, indexT;
        
        for (int i = 0; i < n; ++i) {
            indexS[s[i]] = i;
            indexT[t[i]] = i;
        }
        
        int difference = 0;
        for (char c : s) {
            difference += abs(indexS[c] - indexT[c]);
        }
        
        return difference;          
    }
};
