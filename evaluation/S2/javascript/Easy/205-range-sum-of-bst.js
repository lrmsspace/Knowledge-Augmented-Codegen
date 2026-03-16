// Source: https://leetcode.com/problems/range-sum-of-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].
//
// Example:
// Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
// Output: 32
// Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 2 * 104].
// 	1 <= Node.val <= 105
// 	1 <= low <= high <= 105
// 	All Node.val are unique.
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, merge-sort, binary-search)
//   • When to use: Use when processing range queries or updates on an array, or when efficient searching and sorting of data are required. It's also applicable for problems that can be broken down into smaller, independent subproblems.
//   • Idea: This card describes techniques for efficiently handling range queries and updates on arrays, as well as searching and sorting elements. These methods typically achieve logarithmic time complexity for operations.
//   • Invariants: Each node in the segment tree represents a specific range of the original array.; The target element, if present, is always within the current binary search interval [low, high].
//   • Tips: Segment trees are powerful for static arrays with dynamic queries.; Merge sort's divide-and-conquer approach can be adapted for counting inversions.
//   • Pitfalls: Off-by-one errors in binary search bounds.; Incorrect segment tree node merging logic.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Balanced Search Trees (tree, ds, recursion)
//   • When to use: When needing a self-balancing search tree that guarantees logarithmic time complexity for search and insertion operations. Useful for maintaining data in sorted order with consistent performance, especially when frequent updates are expected.
//   • Idea: A 2-3 tree is a self-balancing search tree where every node has either two children (a 2-node) or three children (a 3-node), ensuring all leaves are at the same depth. It guarantees O(log N) time complexity for search, insertion, and deletion operations.
//   • Invariants: All leaves are at the same depth from the root.; Every node is either a 2-node (one key, two children) or a 3-node (two keys, three children).
//   • Tips: Understand the two node types: 2-nodes (one key, two children) and 3-nodes (two keys, three children).; Insertion always starts by finding the leaf position, then propagates splits upwards if a 4-node is formed.
//   • Pitfalls: Incorrectly handling the promotion of keys during node splits can break the tree's structure.; Forgetting to update parent links after a node split or merge operation.
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
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var rangeSumBST = function(root, low, high) {
    if (root === null) return 0;
    
    let sum = 0;
    
    if (root.val >= low && root.val <= high) {
        sum += root.val;
    }
    
    if (root.val > low) {
        sum += rangeSumBST(root.left, low, high);
    }
    
    if (root.val < high) {
        sum += rangeSumBST(root.right, low, high);
    }
    
    return sum;
};
