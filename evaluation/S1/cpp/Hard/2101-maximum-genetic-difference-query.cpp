// Source: https://leetcode.com/problems/maximum-genetic-difference-query/   |   Difficulty: Hard
//
// Problem Description:
// There is a rooted tree consisting of n nodes numbered 0 to n - 1. Each node's number denotes its unique genetic value (i.e. the genetic value of node x is x). The genetic difference between two genetic values is defined as the bitwise-XOR of their values. You are given the integer array parents, where parents[i] is the parent for node i. If node x is the root of the tree, then parents[x] == -1.
//
// You are also given the array queries where queries[i] = [nodei, vali]. For each query i, find the maximum genetic difference between vali and pi, where pi is the genetic value of any node that is on the path between nodei and the root (including nodei and the root). More formally, you want to maximize vali XOR pi.
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// Example:
// Input: parents = [-1,0,1,1], queries = [[0,2],[3,2],[2,5]]
// Output: [2,3,7]
// Explanation: The queries are processed as follows:
// - [0,2]: The node with the maximum genetic difference is 0, with a difference of 2 XOR 0 = 2.
// - [3,2]: The node with the maximum genetic difference is 1, with a difference of 2 XOR 1 = 3.
// - [2,5]: The node with the maximum genetic difference is 2, with a difference of 5 XOR 2 = 7.
//
// Constraints:
// 2 <= parents.length <= 105
// 	0 <= parents[i] <= parents.length - 1 for every node i that is not the root.
// 	parents[root] == -1
// 	1 <= queries.length <= 3 * 104
// 	0 <= nodei <= parents.length - 1
// 	0 <= vali <= 2 * 105
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
private:
    struct TrieNode {
        TrieNode* children[2] = {nullptr};
        int count = 0;
    };
    
    TrieNode* root;
    vector<vector<int>> children;
    vector<vector<pair<int, int>>> queryByNode; // queryByNode[node] = {query_id, val}
    vector<int> result;
    
    void insert(int num) {
        TrieNode* node = root;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
            node->count++;
        }
    }
    
    void remove(int num) {
        TrieNode* node = root;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            node = node->children[bit];
            node->count--;
        }
    }
    
    int query(int num) {
        TrieNode* node = root;
        int result = 0;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int toggleBit = 1 - bit; // Try to get opposite bit for maximum XOR
            
            if (node->children[toggleBit] && node->children[toggleBit]->count > 0) {
                result |= (1 << i);
                node = node->children[toggleBit];
            } else {
                node = node->children[bit];
            }
        }
        return result;
    }
    
    void dfs(int node) {
        insert(node);
        
        // Process all queries for current node
        for (auto& [queryId, val] : queryByNode[node]) {
            result[queryId] = query(val);
        }
        
        // Traverse all children
        for (int child : children[node]) {
            dfs(child);
        }
        
        remove(node);
    }

public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        root = new TrieNode();
        int n = parents.size();
        children.resize(n);
        queryByNode.resize(n);
        result.resize(queries.size());
        
        // Build the tree structure
        int rootNode = -1;
        for (int i = 0; i < n; i++) {
            if (parents[i] == -1) {
                rootNode = i;
            } else {
                children[parents[i]].push_back(i);
            }
        }
        
        // Group queries by node
        for (int i = 0; i < queries.size(); i++) {
            queryByNode[queries[i][0]].push_back({i, queries[i][1]});
        }
        
        // DFS from root
        dfs(rootNode);
        
        return result;
    }
};
