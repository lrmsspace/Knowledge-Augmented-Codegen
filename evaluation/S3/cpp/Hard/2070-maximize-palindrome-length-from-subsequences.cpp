// Source: https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, word1 and word2. You want to construct a string in the following manner:
//
//
// 	Choose some non-empty subsequence subsequence1 from word1.
// 	Choose some non-empty subsequence subsequence2 from word2.
// 	Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
//
//
// Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.
//
// A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.
//
// A palindrome is a string that reads the same forward as well as backward.
//
// Example:
// Input: word1 = "cacb", word2 = "cbba"
// Output: 5
// Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
//
// Constraints:
// 1 <= word1.length, word2.length <= 1000
// 	word1 and word2 consist of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestPalindrome(string word1, string word2) {
        int n1 = (int)word1.size();
        int n2 = (int)word2.size();
        int maxLen = 0;

        // Check for palindromes that can be formed by characters from both strings
        for (char c = 'a'; c <= 'z'; ++c) {
            int count1 = count(word1.begin(), word1.end(), c);
            int count2 = count(word2.begin(), word2.end(), c);
            if (count1 > 0 && count2 > 0) {
                maxLen = max(maxLen, 2); // At least one character from each string can form a palindrome of length 2
            }
        }

        // Check for palindromes that can be formed by characters from the same string
        maxLen = max(maxLen, longestPalindromeInSingleString(word1));
        maxLen = max(maxLen, longestPalindromeInSingleString(word2));

        return maxLen;          
    }
};
