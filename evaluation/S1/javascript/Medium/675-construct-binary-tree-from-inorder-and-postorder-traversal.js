// Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.
//
// Example:
// Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
// Output: [3,9,20,null,null,15,7]
//
// Constraints:
// 1 <= inorder.length <= 3000
// 	postorder.length == inorder.length
// 	-3000 <= inorder[i], postorder[i] <= 3000
// 	inorder and postorder consist of unique values.
// 	Each value of postorder also appears in inorder.
// 	inorder is guaranteed to be the inorder traversal of the tree.
// 	postorder is guaranteed to be the postorder traversal of the tree.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
//   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
//   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
//   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
//   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
//   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - Binary Search Trees
//  (tree, recursion)
//   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
//   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
//   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
//   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
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
 * @param {number[]} inorder
 * @param {number[]} postorder
 * @return {TreeNode}
 */
var buildTree = function(inorder, postorder) {
    if (inorder.length === 0 || postorder.length === 0) {
        return null;
    }

    const rootValue = postorder[postorder.length - 1];
    const root = new TreeNode(rootValue);

    const rootIndexInInorder = inorder.indexOf(rootValue);

    root.left = buildTree(inorder.slice(0, rootIndexInInorder), postorder.slice(0, rootIndexInInorder));
    root.right = buildTree(inorder.slice(rootIndexInInorder + 1), postorder.slice(rootIndexInInorder, postorder.length - 1));

    return root;
};
