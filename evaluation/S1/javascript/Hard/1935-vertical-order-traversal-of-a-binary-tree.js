// Source: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
//
// For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
//
// The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
//
// Return the vertical order traversal of the binary tree.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
// Explanation:
// Column -1: Only node 9 is in this column.
// Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
// Column 1: Only node 20 is in this column.
// Column 2: Only node 7 is in this column.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Binary Search Trees
//  (tree, enumeration)
//   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
//   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
//   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
//   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
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
 * @return {number[][]}
 */
var verticalTraversal = function(root) {
    const columnTable = new Map();
    const queue = [[root, 0, 0]]; // [node, row, col]

    while (queue.length) {
        const [node, row, col] = queue.shift();
        if (!node) continue;

        if (!columnTable.has(col)) {
            columnTable.set(col, []);
        }
        columnTable.get(col).push([row, node.val]);

        queue.push([node.left, row + 1, col - 1]);
        queue.push([node.right, row + 1, col + 1]);
    }

    const sortedColumns = [...columnTable.keys()].sort((a, b) => a - b);
    const result = [];
    
    for (const col of sortedColumns) {
        const entries = columnTable.get(col);
        entries.sort((a, b) => a[0] === b[0] ? a[1] - b[1] : a[0] - b[0]); // Sort by row, then by value
        result.push(entries.map(entry => entry[1]));
    }
    
    return result;
};
