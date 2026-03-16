// Source: https://leetcode.com/problems/count-nodes-with-the-highest-score/   |   Difficulty: Medium
//
// Problem Description:
// There is a binary tree rooted at 0 consisting of n nodes. The nodes are labeled from 0 to n - 1. You are given a 0-indexed integer array parents representing the tree, where parents[i] is the parent of node i. Since node 0 is the root, parents[0] == -1.
//
// Each node has a score. To find the score of a node, consider if the node and the edges connected to it were removed. The tree would become one or more non-empty subtrees. The size of a subtree is the number of the nodes in it. The score of the node is the product of the sizes of all those subtrees.
//
// Return the number of nodes that have the highest score.
//
// Example:
// Input: parents = [-1,2,0,2,0]
// Output: 3
// Explanation:
// - The score of node 0 is: 3 * 1 = 3
// - The score of node 1 is: 4 = 4
// - The score of node 2 is: 1 * 1 * 2 = 2
// - The score of node 3 is: 4 = 4
// - The score of node 4 is: 4 = 4
// The highest score is 4, and three nodes (node 1, node 3, and node 4) have the highest score.
//
// Constraints:
// n == parents.length
// 	2 <= n <= 105
// 	parents[0] == -1
// 	0 <= parents[i] <= n - 1 for i != 0
// 	parents represents a valid binary tree.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
// - Binary Search Trees
//  (tree, enumeration)
//   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
//   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
//   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
//   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countHighestScoreNodes(int[] parents) {
        int n = parents.length;
        List<List<Integer>> children = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            children.add(new ArrayList<>());
        }
        for (int i = 1; i < n; i++) {
            children.get(parents[i]).add(i);
        }

        long maxScore = 0;
        int count = 0;

        int[] subtreeSizes = new int[n];

        for (int i = 0; i < n; i++) {
            long score = 1;
            int remainingSize = n - 1;

            for (int child : children.get(i)) {
                int childSize = dfs(child, children, subtreeSizes);
                score *= childSize;
                remainingSize -= childSize;
            }

            if (i != 0) {
                score *= remainingSize;
            }

            if (score > maxScore) {
                maxScore = score;
                count = 1;
            } else if (score == maxScore) {
                count++;
            }
        }

        return count;           
    }
}
