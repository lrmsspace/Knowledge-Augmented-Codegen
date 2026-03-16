// Source: https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to the edge between i and parent[i]. s[0] can be ignored.
//
// Return the number of pairs of nodes (u, v) such that u < v and the characters assigned to edges on the path from u to v can be rearranged to form a palindrome.
//
// A string is a palindrome when it reads the same backwards as forwards.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "acaabc"
// Output: 8
// Explanation: The valid pairs are:
// - All the pairs (0,1), (0,2), (1,3), (1,4) and (2,5) result in one character which is always a palindrome.
// - The pair (2,3) result in the string "aca" which is a palindrome.
// - The pair (1,5) result in the string "cac" which is a palindrome.
// - The pair (3,5) result in the string "acac" which can be rearranged into the palindrome "acca".
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists of only lowercase English letters.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Balanced bracket sequences (number, counting)
//   • When to use: When asked to count the total number of valid or well-formed bracket sequences of a certain length or with a specific number of pairs. This often involves combinatorial reasoning or dynamic programming.
//   • Idea: Counts the total number of valid bracket sequences of a given length or with a specific number of pairs, where each opening bracket has a corresponding closing bracket. This problem often has a combinatorial solution, typically involving Catalan numbers, with a time complexity of O(N) or O(N^2) for DP.
//   • Invariants: At any prefix of the sequence, the number of open brackets is greater than or equal to the number of closing brackets.; The total number of open brackets in the sequence equals the total number of closing brackets.
//   • Tips: Recognize the pattern for Catalan numbers if applicable.; Dynamic programming can be used for more complex variations.
//   • Pitfalls: Incorrectly handling the balance constraint (open count >= close count).; Overcounting or undercounting sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long countPalindromePaths(int* parent, int parentSize, char* s) {
    int n = parentSize;
    int *childrenCount = (int*)calloc(n, sizeof(int));
    for (int i = 1; i < n; i++) {
        childrenCount[parent[i]]++;
    }

    int **children = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        if (childrenCount[i] > 0) {
            children[i] = (int*)malloc(childrenCount[i] * sizeof(int));
            childrenCount[i] = 0; // reuse for indexing
        } else {
            children[i] = NULL;
        }
    }
    for (int i = 1; i < n; i++) {
        int p = parent[i];
        children[p][childrenCount[p]++] = i;
    }

    long long result = 0;

    // DFS function to count palindromic paths
    void dfs(int node, int pathMask, int *countMap, int *mapSize) {
        pathMask ^= (1 << (s[node] - 'a'));
        // Count palindromic paths ending at this node
        result += countMap[pathMask];
        for (int bit = 0; bit < 26; bit++) {
            result += countMap[pathMask ^ (1 << bit)];
        }
        // Update count map
        countMap[pathMask]++;
        (*mapSize)++;

        for (int i = 0; i < childrenCount[node]; i++) {
            dfs(children[node][i], pathMask, countMap, mapSize);
        }

        // Backtrack
        countMap[pathMask]--;
        (*mapSize)--;
    }

    int maxMapSize = 1 << 26;
    int *countMap = (int*)calloc(maxMapSize, sizeof(int));
    int mapSize = 0;

    dfs(0, 0, countMap, &mapSize);

    free(countMap);
    for (int i = 0; i < n; i++) {
        if (children[i]) free(children[i]);
    }
    free(children);
    free(childrenCount);

    return result;      
}
