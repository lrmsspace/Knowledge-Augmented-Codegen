// Source: https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes, where each node is uniquely assigned a value from 1 to n. You are also given a sequence of n values voyage, which is the desired pre-order traversal of the binary tree.
//
// Any node in the binary tree can be flipped by swapping its left and right subtrees. For example, flipping node 1 will have the following effect:
//
// Flip the smallest number of nodes so that the pre-order traversal of the tree matches voyage.
//
// Return a list of the values of all flipped nodes. You may return the answer in any order. If it is impossible to flip the nodes in the tree to make the pre-order traversal match voyage, return the list [-1].
//
// Example:
// Input: root = [1,2], voyage = [2,1]
// Output: [-1]
// Explanation: It is impossible to flip the nodes such that the pre-order traversal matches voyage.
//
// Constraints:
// The number of nodes in the tree is n.
// 	n == voyage.length
// 	1 <= n <= 100
// 	1 <= Node.val, voyage[i] <= n
// 	All the values in the tree are unique.
// 	All the values in voyage are unique.
//
// Helpful references (internal KB):
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use when counting labeled trees or converting between a labeled tree and a unique sequence representation for combinatorial analysis. It provides a bijection for problems involving N labeled nodes.
//   • Idea: Prüfer code is a unique sequence of length N-2 that represents a labeled tree with N nodes. It is constructed by iteratively removing the smallest-labeled leaf and recording its neighbor, and can be reconstructed back into the tree.
//   • Invariants: The Prüfer sequence always contains N-2 elements for a tree with N nodes.; At each step of encoding, the removed node is a leaf with the smallest label among all current leaves.
//   • Tips: Maintain an array of node degrees for efficient updates.; Use a min-priority queue to quickly find the smallest-labeled leaf.
//   • Pitfalls: Incorrectly updating node degrees after removal.; Off-by-one errors when dealing with 0-indexed vs. 1-indexed labels.
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
 * @param {number[]} voyage
 * @return {number[]}
 */
var flipMatchVoyage = function(root, voyage) {
  const flipped = [];
  let index = 0;

  function dfs(node) {
    if (!node) {
      return true;
    }
    if (node.val !== voyage[index]) {
      return false;
    }
    index++;
    if (node.left && node.left.val !== voyage[index]) {
      flipped.push(node.val);
      return dfs(node.right) && dfs(node.left);
    }
    return dfs(node.left) && dfs(node.right);
  }

  return dfs(root) ? flipped : [-1];
};
