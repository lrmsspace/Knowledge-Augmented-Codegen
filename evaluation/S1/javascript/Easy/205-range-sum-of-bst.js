// Source: https://leetcode.com/problems/range-sum-of-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].
//
// Example:
// Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
// Output: 32
// Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 2 * 104].
// 	1 <= Node.val <= 105
// 	1 <= low <= high <= 105
// 	All Node.val are unique.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Balanced Search Trees (tree, ds, binary-search, recursion)
//   • When to use: When you need to store a dynamic set of ordered data and require guaranteed logarithmic time complexity for search, insertion, and deletion operations, even in worst-case scenarios.
//   • Idea: Balanced search trees are a class of self-balancing binary search trees that maintain a logarithmic height to ensure O(log N) time complexity for core operations like search, insertion, and deletion. They achieve this balance through structural modifications such as rotations or node splitting/merging.
//   • Invariants: For any node, all keys in its left subtree are less than its key(s), and all keys in its right subtree are greater than its key(s).; The height of the tree is always proportional to log N, ensuring O(log N) operations.
//   • Tips: Understand the specific balancing rules (e.g., AVL rotations, Red-Black tree color properties, 2-3 tree node splits).; Consider the trade-offs between different balanced tree types (e.g., simpler implementation vs. stricter balance).
//   • Pitfalls: Implementation complexity can be high due to intricate rebalancing logic.; Overhead for rebalancing operations might be noticeable for very small N.
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var rangeSumBST = function(root, low, high) {
    let sum = 0;

    function dfs(node) {
        if (!node) return;
        if (node.val >= low && node.val <= high) {
            sum += node.val;
        }
        if (node.val > low) {
            dfs(node.left);
        }
        if (node.val < high) {
            dfs(node.right);
        }
    }

    dfs(root);
    return sum;
};