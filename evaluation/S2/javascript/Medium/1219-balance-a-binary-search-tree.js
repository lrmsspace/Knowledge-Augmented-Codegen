// Source: https://leetcode.com/problems/balance-a-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.
//
// A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.
//
// Example:
// Input: root = [1,null,2,null,3,null,4,null,null]
// Output: [2,1,3,null,null,null,4]
// Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 105
//
// Helpful references (internal KB):
// - Balanced Search Trees (tree, ds, recursion)
//   • When to use: When needing a self-balancing search tree that guarantees logarithmic time complexity for search and insertion operations. Useful for maintaining data in sorted order with consistent performance, especially when frequent updates are expected.
//   • Idea: A 2-3 tree is a self-balancing search tree where every node has either two children (a 2-node) or three children (a 3-node), ensuring all leaves are at the same depth. It guarantees O(log N) time complexity for search, insertion, and deletion operations.
//   • Invariants: All leaves are at the same depth from the root.; Every node is either a 2-node (one key, two children) or a 3-node (two keys, three children).
//   • Tips: Understand the two node types: 2-nodes (one key, two children) and 3-nodes (two keys, three children).; Insertion always starts by finding the leaf position, then propagates splits upwards if a 4-node is formed.
//   • Pitfalls: Incorrectly handling the promotion of keys during node splits can break the tree's structure.; Forgetting to update parent links after a node split or merge operation.
// - Sqrt Tree (array, tree, recursion)
//   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
//   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
//   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
//   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
//   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
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
 * @return {TreeNode}
 */
var balanceBST = function(root) {
    const nodes = [];
    const inorder = (node) => {
        if (!node) return;
        inorder(node.left);
        nodes.push(node);
        inorder(node.right);
    };
    inorder(root);
    
    const buildTree = (left, right) => {
        if (left > right) return null;
        const mid = left + ((right - left) >> 1);
        const node = nodes[mid];
        node.left = buildTree(left, mid - 1);
        node.right = buildTree(mid + 1, right);
        return node;
    };
    
    return buildTree(0, nodes.length - 1);
};
