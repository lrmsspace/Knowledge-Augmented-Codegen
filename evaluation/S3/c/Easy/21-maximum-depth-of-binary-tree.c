// Source: https://leetcode.com/problems/maximum-depth-of-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return its maximum depth.
//
// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: 3
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	-100 <= Node.val <= 100
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use when you need to explore all reachable vertices from a starting point or systematically visit all nodes in a graph or tree. It's suitable for problems requiring full exploration of a branch before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically using a stack (explicit or implicit via recursion).
//   • Invariants: Every node `v` in the graph is either visited or not yet visited.; The recursion stack (or explicit stack) always contains a path from the source node to the current node being explored.
//   • Tips: Use a `visited` array or set to prevent cycles and redundant work.; Recursion is often cleaner for implementation, but iterative DFS with an explicit stack avoids recursion depth limits.
//   • Pitfalls: Stack overflow can occur with deep recursion on large graphs.; Forgetting to mark nodes as visited leads to infinite loops in cyclic graphs.
// - Depth First Search (graph, dfs)
//   • When to use: Use to explore all reachable nodes, find paths, detect cycles, or perform topological sorting. It's also suitable for tree traversals and connected components.
//   • Idea: DFS explores as far as possible along each branch before backtracking. It has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes on the current path from source to current node are marked as visiting.; All nodes already fully explored are marked as visited.
//   • Tips: Use a visited set/array to prevent infinite loops in cyclic graphs.; Recursion stack can lead to stack overflow for deep graphs; consider iterative DFS with an explicit stack.
//   • Pitfalls: Stack overflow with deep recursion on large graphs.; Incorrectly handling visited states can lead to infinite loops or incorrect results.
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
int maxDepth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;       
}
