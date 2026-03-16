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
//  (tree, recursion)
//   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
//   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
//   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
//   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use when you need to represent all positive irreducible fractions in a structured tree or efficiently search for a specific fraction. It's also useful for generating Farey sequences or understanding rational number properties.
//   • Idea: The Stern-Brocot tree is an infinite binary tree containing every positive irreducible fraction exactly once, ordered by value. Searching for a fraction or generating parts of the tree typically involves a logarithmic number of steps relative to the sum of the numerator and denominator, making it efficient for O(log(x+y)) operations.
//   • Invariants: For any node m/n, all fractions in its left subtree are strictly less than m/n.; For any node m/n, all fractions in its right subtree are strictly greater than m/n.
//   • Tips: The mediant of a/b and c/d is (a+c)/(b+d), which is always irreducible if a/b and c/d are.; All fractions in the Stern-Brocot tree are inherently irreducible.
//   • Pitfalls: Integer overflow when calculating mediants if numerators or denominators are very large.; Incorrectly handling the initial 'infinite' fractions (0/1 and 1/0) as boundary conditions.
// - Sqrt Tree (array, number, bitmask-dp, enumeration)
//   • When to use: Used for answering range queries on a static array by recursively decomposing it into square root sized blocks, achieving O(log log N) query time.
//   • Idea: A Sqrt Tree is a recursive data structure that decomposes an array into blocks of square root size, building a similar structure on each block. It allows for efficient range queries, typically achieving O(log log N) query time after an O(N log log N) precomputation.
//   • Invariants: Each node in the Sqrt Tree represents a contiguous segment of the original array.; A node representing a segment of length k has sqrt(k) children, each covering a block of sqrt(k) elements.
//   • Tips: Precompute answers for all possible block combinations within a node.; Handle queries spanning multiple blocks by combining precomputed prefix, suffix, and full block results.
//   • Pitfalls: High constant factors due to complex precomputation per node.; Memory usage can be significant, O(N log log N), for large N.
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
    if (root === null) return null;
    
    if (root.val === val) {
        return root;
    } else if (val < root.val) {
        return searchBST(root.left, val);
    } else {
        return searchBST(root.right, val);
    }
};
