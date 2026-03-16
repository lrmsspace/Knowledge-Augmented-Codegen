// Source: https://leetcode.com/problems/count-the-repetitions/   |   Difficulty: Hard
//
// Problem Description:
// We define str = [s, n] as the string str which consists of the string s concatenated n times.
//
//
// 	For example, str == ["abc", 3] =="abcabcabc".
//
//
// We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
//
//
// 	For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
//
//
// You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
//
// Return the maximum integer m such that str = [str2, m] can be obtained from str1.
//
// Example:
// Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
// Output: 2
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1 and s2 consist of lowercase English letters.
// 	1 <= n1, n2 <= 106
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int s1Len = s1.length();
        int s2Len = s2.length();
        int indexr[s2Len + 1];
        int countr[s2Len + 1];
        memset(indexr, 0, sizeof(indexr));
        memset(countr, 0, sizeof(countr));
        int index = 0;
        int count = 0;
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < s1Len; ++j) {
                if (s1[j] == s2[index]) {
                    index++;
                    if (index == s2Len) {
                        index = 0;
                        count++;
                    }
                }
            }
            indexr[i] = index;
            countr[i] = count;
            for (int k = 0; k < i; ++k) {
                if (indexr[k] == index) {
                    int preCount = countr[k];
                    int patternCount = ((n1 - 1 - k) / (i - k)) * (countr[i] - countr[k]);
                    int remainCount = countr[k + (n1 - 1 - k) % (i - k)] - countr[k];
                    return (preCount + patternCount + remainCount) / n2;
                }
            }
        }
        return countr[n1 - 1] / n2;         
    }
};
