// Source: https://leetcode.com/problems/find-bottom-left-tree-value/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the leftmost value in the last row of the tree.
//
// Example:
// Input: root = [2,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-231 <= Node.val <= 231 - 1
//
// Helpful references (internal KB):
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Range Minimum Query (array, tree, lca)
//   • When to use: Use when needing to find the minimum element within various specified ranges of a static array efficiently, especially when many queries are expected after initial preprocessing.
//   • Idea: Range Minimum Query (RMQ) finds the minimum value in a given contiguous subsegment of an array. It typically involves preprocessing the array to achieve O(1) or O(log N) query time, with preprocessing in O(N log N) or O(N).
//   • Invariants: For a Sparse Table `st[i][j]`, `st[i][j]` stores the minimum in the range `[i, i + 2^j - 1]`.; During a query `[L, R]`, the chosen blocks `[L, L + 2^k - 1]` and `[R - 2^k + 1, R]` completely cover the target range.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; Segment Trees provide O(log N) query and update times, suitable for dynamic arrays.
//   • Pitfalls: Sparse Tables do not support updates efficiently; they are primarily for static data.; Off-by-one errors are common when calculating range indices or log values for segment lengths.
// - Binary Search Trees
//  (tree, quickselect)
//   • When to use: Use when maintaining an ordered collection of elements that requires efficient search, insertion, and deletion operations. It is also suitable for finding minimum, maximum, floor, and ceiling values.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Core operations like search, insert, and delete typically run in O(h) time, where h is the tree's height.
//   • Invariants: For any node, all keys in its left subtree are less than its own key.; For any node, all keys in its right subtree are greater than its own key.
//   • Tips: Maintain subtree sizes for order-statistic operations like finding the k-th smallest element.; Consider self-balancing variants (AVL, Red-Black) to guarantee O(log N) worst-case performance.
//   • Pitfalls: Unbalanced trees can degrade to O(N) performance for all operations.; Forgetting to update parent pointers or subtree sizes during modifications.
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
 * @return {number}
 */
var findBottomLeftValue = function(root) {
    let queue = [root], bottomLeft = root.val;
    while (queue.length > 0) {
        const nextQueue = [];
        for (const node of queue) {
            bottomLeft = node.val;
            if (node.left) nextQueue.push(node.left);
            if (node.right) nextQueue.push(node.right);
        }
        queue = nextQueue;
    }
    return bottomLeft;
};