// Source: https://leetcode.com/problems/delete-leaves-with-a-given-value/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree root and an integer target, delete all the leaf nodes with value target.
//
// Note that once you delete a leaf node with value target, if its parent node becomes a leaf node and has the value target, it should also be deleted (you need to continue doing that until you cannot).
//
// Example:
// Input: root = [1,2,3,2,null,2,4], target = 2
// Output: [1,null,3,null,4]
// Explanation: Leaf nodes in green with value (target = 2) are removed (Picture in left). 
// After removing, new nodes become leaf nodes with value (target = 2) (Picture in center).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3000].
// 	1 <= Node.val, target <= 1000
//
// Helpful references (internal KB):
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Segment Tree (tree, array, segment-tree, merge-sort, binary-search)
//   • When to use: Use when processing range queries or updates on an array, or when efficient searching and sorting of data are required. It's also applicable for problems that can be broken down into smaller, independent subproblems.
//   • Idea: This card describes techniques for efficiently handling range queries and updates on arrays, as well as searching and sorting elements. These methods typically achieve logarithmic time complexity for operations.
//   • Invariants: Each node in the segment tree represents a specific range of the original array.; The target element, if present, is always within the current binary search interval [low, high].
//   • Tips: Segment trees are powerful for static arrays with dynamic queries.; Merge sort's divide-and-conquer approach can be adapted for counting inversions.
//   • Pitfalls: Off-by-one errors in binary search bounds.; Incorrect segment tree node merging logic.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
//   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
//   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
//   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
//   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
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
 * @param {number} target
 * @return {TreeNode}
 */
var removeLeafNodes = function(root, target) {
    if (!root) return null;
    root.left = removeLeafNodes(root.left, target);
    root.right = removeLeafNodes(root.right, target);
    if (!root.left && !root.right && root.val === target) {
        return null;
    }
    return root;
};
