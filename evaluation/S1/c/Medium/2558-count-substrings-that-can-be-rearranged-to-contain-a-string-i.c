// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 105
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long validSubstringCount(char* word1, char* word2) {
    int len1 = 0, len2 = 0;
    while (word1[len1]) len1++;
    while (word2[len2]) len2++;

    int count2[26] = {0};
    for (int i = 0; i < len2; i++) {
        count2[word2[i] - 'a']++;
    }

    long long result = 0;
    int count1[26] = {0};
    for (int i = 0; i < len1; i++) {
        count1[word1[i] - 'a']++;
        if (i >= len2) {
            count1[word1[i - len2] - 'a']--;
        }
        if (i >= len2 - 1) {
            int valid = 1;
            for (int j = 0; j < 26; j++) {
                if (count1[j] < count2[j]) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                result++;
            }
        }
    }

    return result;      
}
