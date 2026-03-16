// Source: https://leetcode.com/problems/search-in-a-binary-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// You are given the root of a binary search tree (BST) and an integer val.
//
// Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.
//
// Example:
// Input: root = [4,2,7,1,3], val = 2
// Output: [2,1,3]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 5000].
// 	1 <= Node.val <= 107
// 	root is a binary search tree.
// 	1 <= val <= 107
//
// Helpful references (internal KB):
// - Binary Search Trees
//  (tree, quickselect)
//   • When to use: Use when maintaining an ordered collection of elements that requires efficient search, insertion, and deletion operations. It is also suitable for finding minimum, maximum, floor, and ceiling values.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Core operations like search, insert, and delete typically run in O(h) time, where h is the tree's height.
//   • Invariants: For any node, all keys in its left subtree are less than its own key.; For any node, all keys in its right subtree are greater than its own key.
//   • Tips: Maintain subtree sizes for order-statistic operations like finding the k-th smallest element.; Consider self-balancing variants (AVL, Red-Black) to guarantee O(log N) worst-case performance.
//   • Pitfalls: Unbalanced trees can degrade to O(N) performance for all operations.; Forgetting to update parent pointers or subtree sizes during modifications.
// - Binary Search Trees
//  (tree, recursion)
//   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
//   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
//   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
//   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
// - Treap (Cartesian tree) (tree, recursion, binary-search)
//   • When to use: When you need a self-balancing binary search tree that supports efficient split and merge operations, often used for dynamic set management or range queries on mutable data.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on priorities (randomly assigned). It supports efficient operations like split and merge, typically with an average time complexity of O(log N).
//   • Invariants: For any node, its key is greater than or equal to all keys in its left subtree.; For any node, its key is less than all keys in its right subtree.
//   • Tips: Understand the recursive nature of Split and Merge operations.; Randomly assign priorities (Y values) to ensure probabilistic balancing.
//   • Pitfalls: Incorrect handling of null pointers or empty subtrees in recursion.; Forgetting to update parent pointers or root pointers after operations.
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
 * @param {number} val
 * @return {TreeNode}
 */
var searchBST = function(root, val) {
    if (root === null) {
        return null;
    }
    if (root.val === val) {
        return root;
    }
    if (val < root.val) {
        return searchBST(root.left, val);
    }
    return searchBST(root.right, val);
};
