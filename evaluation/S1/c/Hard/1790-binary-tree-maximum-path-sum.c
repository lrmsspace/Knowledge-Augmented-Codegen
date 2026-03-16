// Source: https://leetcode.com/problems/binary-tree-maximum-path-sum/   |   Difficulty: Hard
//
// Problem Description:
// A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
//
// The path sum of a path is the sum of the node's values in the path.
//
// Given the root of a binary tree, return the maximum path sum of any non-empty path.
//
// Example:
// Input: root = [1,2,3]
// Output: 6
// Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3 * 104].
// 	-1000 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Kuhn's Algorithm for Maximum Bipartite Matching (graph, array, greedy, dfs)
//   • When to use: Use when finding a maximum matching in a bipartite graph, particularly when performance on random graphs can be improved by heuristic pre-matching.
//   • Idea: This algorithm finds a maximum matching in a bipartite graph by iteratively searching for augmenting paths using Depth-First Search. An improved version incorporates greedy heuristics to find an initial matching, potentially speeding up practical runtime while maintaining the O(V*E) worst-case complexity.
//   • Invariants: After each successful DFS call, the size of the current matching increases by one.; The 'mt' array correctly stores the current matching pairs for all vertices.
//   • Tips: Pre-calculate an initial matching using a simple heuristic to reduce DFS calls.; Consider heuristics like iterating over vertices or selecting from smallest degree vertices first.
//   • Pitfalls: Forgetting to reset the 'visited' array for each new DFS search in the main loop.; Incorrectly modifying the main loop logic when integrating heuristic pre-matching.
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
int maxPathSum(struct TreeNode* root) {
    int maxSum = -1000000;

    int dfs(struct TreeNode* node) {
        if (!node) return 0;
        int leftMax = dfs(node->left);
        int rightMax = dfs(node->right);
        if (leftMax < 0) leftMax = 0;
        if (rightMax < 0) rightMax = 0;
        int currentSum = node->val + leftMax + rightMax;
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
        return node->val + (leftMax > rightMax ? leftMax : rightMax);
    }

    dfs(root);
    return maxSum;      
}
