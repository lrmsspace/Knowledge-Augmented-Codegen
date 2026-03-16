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
// - Aho-Corasick algorithm (trie, graph, bfs, trie-match)
//   • When to use: Use this algorithm to efficiently find all occurrences of a fixed set of patterns within a larger text. It is ideal for scenarios requiring simultaneous searching for multiple dictionary words.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing linear time searching for all pattern occurrences in a text. It extends a trie with suffix links and failure transitions for efficient traversal, achieving O(N + M + K) complexity where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All nodes at depth 'd' have their suffix links correctly computed before processing nodes at depth 'd+1'.; For any node 'u', its suffix link points to the longest proper suffix of the string represented by 'u' that is also a prefix of some pattern.
//   • Tips: Build the trie from all patterns first, marking nodes that represent the end of a pattern.; Compute suffix links using a breadth-first search (BFS) starting from the root.
//   • Pitfalls: Incorrectly computing suffix links can lead to wrong matches or infinite loops.; High memory usage can occur for large alphabets or a vast number of patterns.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool pyramidTransition(char* bottom, char** allowed, int allowedSize) {
    // This problem can be solved using Depth-First Search (DFS) to explore all possible ways to build the pyramid from the given bottom row. We will use a recursive helper function to perform the DFS and check if we can reach the top of the pyramid while adhering to the allowed patterns.

    // Create a mapping from pairs of blocks to possible top blocks based on the allowed patterns
    char* map[36][36]; // 6 letters * 6 letters = 36 possible pairs
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 36; j++) {
            map[i][j] = NULL; // Initialize all entries to NULL
        }
    }
    
    for (int i = 0; i < allowedSize; i++) {
        char* pattern = allowed[i];
        int left = pattern[0] - 'A';
        int right = pattern[1] - 'A';
        char top = pattern[2];
        
        // Append the top block to the list of possible tops for this pair
        if (map[left][right] == NULL) {
            map[left][right] = (char*)malloc(7 * sizeof(char)); // Max 6 tops + null terminator
            map[left][right][0] = '\0'; // Start with an empty string
        }
        strncat(map[left][right], &top, 1); // Append the top character
    }
    
    // Recursive DFS function to build the pyramid
    bool dfs(char* current) {
        int len = strlen(current);
        if (len == 1) return true; // Reached the top successfully
        
        char next[7]; // To store possible next level blocks
        for (int i = 0; i < len - 1; i++) {
            int left = current[i] - 'A';
            int right = current[i + 1] - 'A';
            if (map[left][right] == NULL) return false; // No allowed pattern for this pair
            
            if (i == 0) {
                strcpy(next, map[left][right]); // Initialize next with possible tops for the first pair
            } else {
                char temp[7];
                strcpy(temp, next); // Store current next options
                next[0] = '\0'; // Reset next
                for (int j = 0; temp[j] != '\0'; j++) {
                    char top = temp[j];
                    if (strchr(map[left][right], top) != NULL) {
                        strncat(next, &top, 1); // Append valid top character
                    }
                }
                if (next[0] == '\0') return false; // No valid tops for this pair
            }
        }
        return dfs(next); // Recur with the next level
    }
    return dfs(bottom); 
}
