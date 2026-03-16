// Source: https://leetcode.com/problems/smallest-string-starting-from-leaf/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree where each node has a value in the range [0, 25] representing the letters 'a' to 'z'.
//
// Return the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
//
// As a reminder, any shorter prefix of a string is lexicographically smaller.
//
//
// 	For example, "ab" is lexicographically smaller than "aba".
//
//
// A leaf of a node is a node that has no children.
//
// Example:
// Input: root = [0,1,2,3,4,3,4]
// Output: "dba"
//
// Constraints:
// The number of nodes in the tree is in the range [1, 8500].
// 	0 <= Node.val <= 25
//
// Helpful references (internal KB):
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Search for connected components in a graph (stack, graph, dfs, recursion)
//   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
//   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
//   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
//   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
//   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
// - 0-1 BFS (graph, deque, 01-bfs, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
//   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
//   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
//   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
//   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
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
    private String dfs(TreeNode node, StringBuilder path) {
        if (node == null) {
            return "~"; // A character larger than 'z' to ensure non-leaf paths are not chosen
        }
        
        path.append((char) ('a' + node.val));
        
        // If it's a leaf node, return the current path reversed
        if (node.left == null && node.right == null) {
            String leafPath = path.reverse().toString();
            path.reverse(); // Restore original order for backtracking
            return leafPath;
        }
        
        String leftPath = dfs(node.left, path);
        String rightPath = dfs(node.right, path);
        
        path.deleteCharAt(path.length() - 1); // Backtrack
        
        return leftPath.compareTo(rightPath) < 0 ? leftPath : rightPath;
    }
    public String smallestFromLeaf(TreeNode root) {
        return dfs(root, new StringBuilder());          
    }
}
