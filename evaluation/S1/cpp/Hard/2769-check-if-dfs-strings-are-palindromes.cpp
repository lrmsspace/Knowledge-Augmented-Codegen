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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> children(n);
        for (int i = 1; i < n; ++i) {
            children[parent[i]].push_back(i);
        }

        vector<bool> result(n, true);

        function<uint32_t(int)> dfs = [&](int node) -> uint32_t {
            uint32_t mask = 0;
            for (int child : children[node]) {
                mask ^= dfs(child);
            }
            mask ^= (1u << (s[node] - 'a'));
            // Check if mask has at most one bit set
            result[node] = (mask & (mask - 1)) == 0;
            return mask;
        };

        dfs(0);
        return result;          
    }
};
