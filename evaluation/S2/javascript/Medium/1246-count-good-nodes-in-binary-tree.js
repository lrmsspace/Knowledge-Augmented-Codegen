// Source: https://leetcode.com/problems/count-good-nodes-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
//
// Return the number of good nodes in the binary tree.
//
// Example:
// Input: root = [3,1,4,3,null,1,5]
// Output: 4
// Explanation: Nodes in blue are good.
// Root Node (3) is always a good node.
// Node 4 -> (3,4) is the maximum value in the path starting from the root.
// Node 5 -> (3,4,5) is the maximum value in the path
// Node 3 -> (3,1,3) is the maximum value in the path.
//
// Constraints:
// The number of nodes in the binary tree is in the range [1, 10^5].
// 	Each node's value is between [-10^4, 10^4].
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
 * @param {TreeNode} root
 * @return {number}
 */
var goodNodes = function(root) {
    let count = 0;
    const dfs = (node, maxSoFar) => {
        if (!node) return;
        if (node.val >= maxSoFar) {
            count++;
            maxSoFar = node.val;
        }
        dfs(node.left, maxSoFar);
        dfs(node.right, maxSoFar);
    };
    dfs(root, -Infinity);
    return count;
};
