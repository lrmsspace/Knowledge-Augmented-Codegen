// Source: https://leetcode.com/problems/find-and-replace-in-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s that you must perform k replacement operations on. The replacement operations are given as three 0-indexed parallel arrays, indices, sources, and targets, all of length k.
//
// To complete the ith replacement operation:
//
//
// 	Check if the substring sources[i] occurs at index indices[i] in the original string s.
// 	If it does not occur, do nothing.
// 	Otherwise if it does occur, replace that substring with targets[i].
//
//
// For example, if s = "abcd", indices[i] = 0, sources[i] = "ab", and targets[i] = "eee", then the result of this replacement will be "eeecd".
//
// All replacement operations must occur simultaneously, meaning the replacement operations should not affect the indexing of each other. The testcases will be generated such that the replacements will not overlap.
//
//
// 	For example, a testcase with s = "abc", indices = [0, 1], and sources = ["ab","bc"] will not be generated because the "ab" and "bc" replacements overlap.
//
//
// Return the resulting string after performing all replacement operations on s.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets = ["eee", "ffff"]
// Output: "eeebffff"
// Explanation:
// "a" occurs at index 0 in s, so we replace it with "eee".
// "cd" occurs at index 2 in s, so we replace it with "ffff".
//
// Constraints:
// 1 <= s.length <= 1000
// 	k == indices.length == sources.length == targets.length
// 	1 <= k <= 100
// 	0 <= indexes[i] < s.length
// 	1 <= sources[i].length, targets[i].length <= 50
// 	s consists of only lowercase English letters.
// 	sources[i] and targets[i] consist of only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* findReplaceString(char* s, int* indices, int indicesSize, char** sources, int sourcesSize, char** targets, int targetsSize) {
    int n = strlen(s);
    char* result = (char*)malloc(3000 * sizeof(char));
    int resIndex = 0;
    int i = 0, j = 0;

    while (i < n) {
        if (j < indicesSize && i == indices[j]) {
            int srcLen = strlen(sources[j]);
            if (strncmp(s + i, sources[j], srcLen) == 0) {
                int tgtLen = strlen(targets[j]);
                strncpy(result + resIndex, targets[j], tgtLen);
                resIndex += tgtLen;
                i += srcLen;
            } else {
                result[resIndex++] = s[i++];
            }
            j++;
        } else {
            result[resIndex++] = s[i++];
        }
    }

    result[resIndex] = '\0';
    return result;      
}
