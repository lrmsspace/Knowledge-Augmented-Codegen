// Source: https://leetcode.com/problems/check-if-dfs-strings-are-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree rooted at node 0, consisting of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// Consider an empty string dfsStr, and define a recursive function dfs(int x) that takes a node x as a parameter and performs the following steps in order:
//
//
// 	Iterate over each child y of x in increasing order of their numbers, and call dfs(y).
// 	Add the character s[x] to the end of the string dfsStr.
//
//
// Note that dfsStr is shared across all recursive calls of dfs.
//
// You need to find a boolean array answer of size n, where for each index i from 0 to n - 1, you do the following:
//
//
// 	Empty the string dfsStr and call dfs(i).
// 	If the resulting string dfsStr is a palindrome, then set answer[i] to true. Otherwise, set answer[i] to false.
//
//
// Return the array answer.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "aababa"
//
// Output: [true,true,false,true,true,true]
//
// Explanation:
//
//
// 	Calling dfs(0) results in the string dfsStr = "abaaba", which is a palindrome.
// 	Calling dfs(1) results in the string dfsStr = "aba", which is a palindrome.
// 	Calling dfs(2) results in the string dfsStr = "ab", which is not a palindrome.
// 	Calling dfs(3) results in the string dfsStr = "a", which is a palindrome.
// 	Calling dfs(4) results in the string dfsStr = "b", which is a palindrome.
// 	Calling dfs(5) results in the string dfsStr = "a", which is a palindrome.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1.
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* findAnswer(int* parent, int parentSize, char* s, int* returnSize) {
    if (!parent || parentSize <= 0 || !s || !returnSize) return NULL;

    int n = parentSize;
    *returnSize = n;
    bool* answer = (bool*)malloc(n * sizeof(bool));
    if (!answer) return NULL;

    // Build adjacency list for the tree
    int* childrenCount = (int*)calloc(n, sizeof(int));
    for (int i = 1; i < n; ++i) {
        childrenCount[parent[i]]++;
    }
    int** children = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        children[i] = (int*)malloc(childrenCount[i] * sizeof(int));
        childrenCount[i] = 0; // reset to use as index
    }
    for (int i = 1; i < n; ++i) {
        children[parent[i]][childrenCount[parent[i]]++] = i;
    }

    // Precompute powers for hashing
    const int p1 = 31, p2 = 37;
    const int m1 = 1e9 + 7, m2 = 1e9 + 9;
    long long* pPower1 = (long long*)malloc((n + 1) * sizeof(long long));
    long long* pPower2 = (long long*)malloc((n + 1) * sizeof(long long));
    pPower1[0] = pPower2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pPower1[i] = (pPower1[i - 1] * p1) % m1;
        pPower2[i] = (pPower2[i - 1] * p2) % m2;
    }

    // DFS function to compute hashes
    void dfs(int node, long long* hashForward1, long long* hashBackward1, long long* hashForward2, long long* hashBackward2, int depth) {
        // Update forward hashes
        hashForward1[depth] = (hashForward1[depth - 1] + (s[node] - 'a' + 1) * pPower1[depth]) % m1;
        hashForward2[depth] = (hashForward2[depth - 1] + (s[node] - 'a' + 1) * pPower2[depth]) % m2;

        // Update backward hashes
        hashBackward1[depth] = (hashBackward1[depth - 1] * p1 + (s[node] - 'a' + 1)) % m1;
        hashBackward2[depth] = (hashBackward2[depth - 1] * p2 + (s[node] - 'a' + 1)) % m2;

        // Check palindrome condition
        if (hashForward1[depth] == (hashBackward1[depth] * pPower1[n - depth]) % m1 &&
            hashForward2[depth] == (hashBackward2[depth] * pPower2[n - depth]) % m2) {
            answer[node] = true;
        } else {
            answer[node] = false;
        }

        // Recurse for children
        for (int i = 0; i < childrenCount[node]; ++i) {
            dfs(children[node][i], hashForward1, hashBackward1, hashForward2, hashBackward2, depth + 1);
        }
    }
    long long* hashForward1 = (long long*)calloc(n + 1, sizeof(long long));
    long long* hashBackward1 = (long long*)calloc(n + 1, sizeof(long long));
    long long* hashForward2 = (long long*)calloc(n + 1, sizeof(long long));
    long long* hashBackward2 = (long long*)calloc(n + 1, sizeof(long long));
    dfs(0, hashForward1, hashBackward1, hashForward2, hashBackward2, 1);
    free(hashForward1);
    free(hashBackward1);
    free(hashForward2);
    free(hashBackward2);
    // Free adjacency list and powers
    for (int i = 0; i < n; ++i) {
        free(children[i]);
    }
    free(children);
    free(childrenCount);
    free(pPower1);
    free(pPower2);
    return answer;
}
