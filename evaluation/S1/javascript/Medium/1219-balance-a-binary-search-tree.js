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
// - Binary Search Trees
//  (tree, enumeration)
//   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
//   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
//   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
//   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
// - Range Minimum Query (array, tree, divide-and-conquer)
//   • When to use: When needing to find the minimum (or maximum) value within various specified ranges of an array efficiently. Suitable for scenarios with many queries on a fixed or frequently updated dataset.
//   • Idea: This technique precomputes answers for subproblems, typically by building a tree-like structure or a table, to efficiently answer queries for the minimum (or maximum) value within a given range. It achieves O(log N) or O(1) query time after O(N log N) or O(N) preprocessing, depending on the specific data structure used.
//   • Invariants: For a Segment Tree node covering range [L, R], its value stores the minimum of all elements in the original array from index L to R.; For any query range [Q_L, Q_R], the combined result from relevant tree nodes correctly represents the minimum in [Q_L, Q_R].
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; For dynamic arrays with updates, Segment Tree offers O(log N) query and update time after O(N) preprocessing.
//   • Pitfalls: Off-by-one errors when defining range boundaries or calculating indices.; Incorrect merge logic for segment tree nodes (e.g., using sum instead of min).
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

	const inOrderTraversal = (node) => {
		if (!node) return;
		inOrderTraversal(node.left);
		nodes.push(node);
		inOrderTraversal(node.right);
	};

	inOrderTraversal(root);

	const buildBalancedBST = (start, end) => {
		if (start > end) return null;
		const mid = Math.floor((start + end) / 2);
		const node = nodes[mid];
		node.left = buildBalancedBST(start, mid - 1);
		node.right = buildBalancedBST(mid + 1, end);
		return node;
	};

	return buildBalancedBST(0, nodes.length - 1);
};
