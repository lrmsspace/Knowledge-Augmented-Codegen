// Source: https://leetcode.com/problems/pyramid-transition-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are stacking blocks to form a pyramid. Each block has a color, which is represented by a single letter. Each row of blocks contains one less block than the row beneath it and is centered on top.
//
// To make the pyramid aesthetically pleasing, there are only specific triangular patterns that are allowed. A triangular pattern consists of a single block stacked on top of two blocks. The patterns are given as a list of three-letter strings allowed, where the first two characters of a pattern represent the left and right bottom blocks respectively, and the third character is the top block.
//
//
// 	For example, "ABC" represents a triangular pattern with a 'C' block stacked on top of an 'A' (left) and 'B' (right) block. Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.
//
//
// You start with a bottom row of blocks bottom, given as a single string, that you must use as the base of the pyramid.
//
// Given bottom and allowed, return true if you can build the pyramid all the way to the top such that every triangular pattern in the pyramid is in allowed, or false otherwise.
//
// Example:
// Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
// Output: true
// Explanation: The allowed triangular patterns are shown on the right.
// Starting from the bottom (level 3), we can build "CE" on level 2 and then build "A" on level 1.
// There are three triangular patterns in the pyramid, which are "BCC", "CDE", and "CEA". All are allowed.
//
// Constraints:
// 2 <= bottom.length <= 6
// 	0 <= allowed.length <= 216
// 	allowed[i].length == 3
// 	The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
// 	All the values of allowed are unique.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Aho-Corasick Algorithm for Pattern Searching (trie, queue, bitset, aho-corasick, bfs)
//   • When to use: Use when searching for multiple patterns simultaneously within a larger text. It is highly efficient for finding all occurrences of a dictionary of keywords.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing efficient simultaneous searching for all patterns in a text. It typically achieves O(N + M + K) time complexity, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented as paths in the trie structure.; For any state `s`, its failure link `fail[s]` points to the longest proper prefix of the string represented by `s` that is also a suffix of `s` and exists in the trie.
//   • Tips: Build the trie first from all patterns, representing each pattern as a path.; Use BFS to construct failure links, pointing to the longest proper prefix of the current state's string that is also a suffix.
//   • Pitfalls: Incorrectly building failure links can lead to wrong matches or infinite loops.; High memory usage if the pattern set is very large or patterns are excessively long.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool pyramidTransition(char* bottom, char** allowed, int allowedSize) {
    int len = strlen(bottom);
    if (len == 1) {
        return true;
    }

    // Create a mapping from pairs of characters to possible top characters
    char map[6][6][7] = {{{0}}}; // 6 letters (A-F), each pair can have up to 6 possible tops
    for (int i = 0; i < allowedSize; i++) {
        int left = allowed[i][0] - 'A';
        int right = allowed[i][1] - 'A';
        int top = allowed[i][2];
        int count = 0;
        while (map[left][right][count] != 0) {
            count++;
        }
        map[left][right][count] = top;
    }

    // Backtracking function to build the pyramid
    bool backtrack(char* current, int level) {
        if (level == 1) {
            return true; // Reached the top
        }
        int nextLen = level - 1;
        char next[nextLen + 1];
        next[nextLen] = '\0';

        // Generate all possible next levels
        void dfs(int index) {
            if (index == nextLen) {
                if (backtrack(next, nextLen)) {
                    return true;
                }
                return false;
            }
            int left = current[index] - 'A';
            int right = current[index + 1] - 'A';
            for (int i = 0; i < 6 && map[left][right][i] != 0; i++) {
                next[index] = map[left][right][i];
                if (dfs(index + 1)) {
                    return true;
                }
            }
            return false;
        }

        return dfs(0);
    }

    return backtrack(bottom, len);
}
