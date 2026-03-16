// Source: https://leetcode.com/problems/decode-ways-ii/   |   Difficulty: Hard
//
// Problem Description:
// A message containing letters from A-Z can be encoded into numbers using the following mapping:
//
//
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
//
//
// To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:
//
//
// 	"AAJF" with the grouping (1 1 10 6)
// 	"KJF" with the grouping (11 10 6)
//
//
// Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".
//
// In addition to the mapping above, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded). For example, the encoded message "1*" may represent any of the encoded messages "11", "12", "13", "14", "15", "16", "17", "18", or "19". Decoding "1*" is equivalent to decoding any of the encoded messages it can represent.
//
// Given a string s consisting of digits and '*' characters, return the number of ways to decode it.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: s = "*"
// Output: 9
// Explanation: The encoded message can represent any of the encoded messages "1", "2", "3", "4", "5", "6", "7", "8", or "9".
// Each of these can be decoded to the strings "A", "B", "C", "D", "E", "F", "G", "H", and "I" respectively.
// Hence, there are a total of 9 ways to decode "*".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is a digit or '*'.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Aho-Corasick Algorithm for Pattern Searching (string, trie, aho-corasick, simulation)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns within a larger text efficiently. It's particularly effective for scenarios involving many patterns and potential overlaps.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses it to find all occurrences of these patterns in a text in a single pass. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented in the trie (goto function).; The failure link `f[u]` for any state `u` points to the state representing the longest proper suffix of the string corresponding to `u` that is also a prefix of some pattern.
//   • Tips: Build the trie (goto function) first from all patterns.; Construct failure links using a BFS-like approach to ensure correct shortest suffix matching.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to propagate output matches through failure links can miss valid pattern occurrences.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numDecodings(char* s) {
    int mod = 1000000007;
    int n = strlen(s);
    long long dp[n + 1];
    dp[0] = 1; // Base case: there's one way to decode an empty string

    // Handle the first character
    if (s[0] == '0') {
        return 0; // No valid encoding starts with '0'
    } else if (s[0] == '*') {
        dp[1] = 9; // '*' can represent digits '1' to '9'
    } else {
        dp[1] = 1; // Any non-zero digit can be decoded as a single character
    }

    for (int i = 2; i <= n; i++) {
        char current = s[i - 1];
        char previous = s[i - 2];

        // Single character decoding
        if (current == '*') {
            dp[i] += 9 * dp[i - 1]; // '*' can represent '1' to '9'
        } else if (current != '0') {
            dp[i] += dp[i - 1]; // Non-zero digit can be decoded as a single character
        }

        // Two character decoding
        if (previous == '*') {
            if (current == '*') {
                dp[i] += 15 * dp[i - 2]; // '**' can represent '11' to '19' and '21' to '26'
            } else if (current >= '0' && current <= '6') {
                dp[i] += 2 * dp[i - 2]; // '*x' can represent '1x' and '2x'
            } else {
                dp[i] += dp[i - 2]; // '*x' can only represent '1x'
            }
        } else if (previous == '1') {
            if (current == '*') {
                dp[i] += 9 * dp[i - 2]; // '1*' can represent '11' to '19'
            } else {
                dp[i] += dp[i - 2]; // '1x' can represent a valid two-digit number
            }
        } else if (previous == '2') {
            if (current == '*') {
                dp[i] += 6 * dp[i - 2]; // '2*' can    
represent '21' to '26'
            } else if (current >= '0' && current <= '6') {
                dp[i] += dp[i - 2]; // '2x' can represent a valid two-digit number
            }
        }
        dp[i] %= mod; // Take modulo to prevent overflow
    }
    return (int)dp[n];
}
