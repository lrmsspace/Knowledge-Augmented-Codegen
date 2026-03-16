// Source: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, flatten the tree into a "linked list":
//
//
// 	The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
// 	The "linked list" should be in the same order as a pre-order traversal of the binary tree.
//
// Example:
// Input: root = [1,2,5,3,4,null,6]
// Output: [1,null,2,null,3,null,4,null,5,null,6]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 2000].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Can you flatten the tree in-place (with O(1) extra space)?
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
//   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
//   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
//   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
//   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
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
    public void flatten(TreeNode root) {
        if (root == null) {
            return;
        }
        
        flatten(root.left);
        flatten(root.right);
        
        TreeNode leftSubtree = root.left;
        TreeNode rightSubtree = root.right;
        
        root.left = null;
        root.right = leftSubtree;
        
        TreeNode current = root;
        while (current.right != null) {
            current = current.right;
        }
        
        current.right = rightSubtree;

    }
}
