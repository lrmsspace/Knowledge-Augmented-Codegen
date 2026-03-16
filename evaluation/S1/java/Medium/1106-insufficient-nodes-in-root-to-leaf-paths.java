// Source: https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer limit, delete all insufficient nodes in the tree simultaneously, and return the root of the resulting binary tree.
//
// A node is insufficient if every root to leaf path intersecting this node has a sum strictly less than limit.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
// Output: [1,2,3,4,null,null,7,8,9,null,14]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 5000].
// 	-105 <= Node.val <= 105
// 	-109 <= limit <= 109
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    private boolean dfs(TreeNode node, int currSum, int limit) {
        if (node == null) {
            return false;
        }

        currSum += node.val;

        // If it's a leaf node, check if the path sum meets the limit
        if (node.left == null && node.right == null) {
            return currSum >= limit;
        }

        // Recursively check left and right subtrees
        boolean leftSufficient = dfs(node.left, currSum, limit);
        boolean rightSufficient = dfs(node.right, currSum, limit);

        // If left subtree is insufficient, prune it
        if (!leftSufficient) {
            node.left = null;
        }
        // If right subtree is insufficient, prune it
        if (!rightSufficient) {
            node.right = null;
        }

        // Return true if either subtree is sufficient
        return leftSufficient || rightSufficient;
    }
    public TreeNode sufficientSubset(TreeNode root, int limit) {
        return dfs(root, 0, limit) ? root : null;           
    }
}
