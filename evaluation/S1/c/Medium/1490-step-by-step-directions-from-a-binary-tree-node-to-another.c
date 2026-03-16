// Source: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.
//
// Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:
//
//
// 	'L' means to go from a node to its left child node.
// 	'R' means to go from a node to its right child node.
// 	'U' means to go from a node to its parent node.
//
//
// Return the step-by-step directions of the shortest path from node s to node t.
//
// Example:
// Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
// Output: "UURL"
// Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	1 <= startValue, destValue <= n
// 	startValue != destValue
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
char* getDirections(struct TreeNode* root, int startValue, int destValue) {
    #define MAX_NODES 100005
    #define MAX_LOG 17  // Since 2^17 > 100000

    typedef struct {
        int parent;
        int depth;
        int up[MAX_LOG];
    } NodeInfo;

    NodeInfo nodeInfo[MAX_NODES];
    int foundStart = 0, foundDest = 0;

    void dfs(struct TreeNode* node, int parent, int depth) {
        if (!node) return;
        nodeInfo[node->val].parent = parent;
        nodeInfo[node->val].depth = depth;
        nodeInfo[node->val].up[0] = parent;
        for (int j = 1; j < MAX_LOG; j++) {
            int midAncestor = nodeInfo[node->val].up[j - 1];
            nodeInfo[node->val].up[j] = midAncestor ? nodeInfo[midAncestor].up[j - 1] : 0;
        }
        dfs(node->left, node->val, depth + 1);
        dfs(node->right, node->val, depth + 1);
    }

    dfs(root, 0, 0);

    int lca(int u, int v) {
        if (nodeInfo[u].depth < nodeInfo[v].depth) {
            int temp = u; u = v; v = temp;
        }
        for (int j = MAX_LOG - 1; j >= 0; j--) {
            if (nodeInfo[u].depth - (1 << j) >= nodeInfo[v].depth) {
                u = nodeInfo[u].up[j];
            }
        }
        if (u == v) return u;
        for (int j = MAX_LOG - 1; j >= 0; j--) {
            if (nodeInfo[u].up[j] != nodeInfo[v].up[j]) {
                u = nodeInfo[u].up[j];
                v = nodeInfo[v].up[j];
            }
        }
        return nodeInfo[u].parent;
    }

    int ancestor = lca(startValue, destValue);

    char pathToStart[MAX_NODES], pathToDest[MAX_NODES];
    int idxStart = 0, idxDest = 0;

    for (int curr = startValue; curr != ancestor; curr = nodeInfo[curr].parent) {
        pathToStart[idxStart++] = 'U';
    }   
    for (int curr = destValue; curr != ancestor; ) {
        int parent = nodeInfo[curr].parent;
        if (nodeInfo[parent].left && nodeInfo[parent].left->val == curr) {
            pathToDest[idxDest++] = 'L';
        } else {
            pathToDest[idxDest++] = 'R';
        }
        curr = parent;
    }
    char* result = (char*)malloc(idxStart + idxDest + 1);
    int resIdx = 0;
    for (int i = 0; i < idxStart; i++) {
        result[resIdx++] = pathToStart[i];
    }
    for (int i = idxDest - 1; i >= 0; i--) {
        result[resIdx++] = pathToDest[i];
    }
    result[resIdx] = '\0';
    return result;
}
