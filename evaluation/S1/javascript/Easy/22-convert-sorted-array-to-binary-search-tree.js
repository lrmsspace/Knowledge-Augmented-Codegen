// Source: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.
//
// Example:
// Input: nums = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
// Explanation: [0,-10,5,null,-3,null,9] is also accepted:
//
// Constraints:
// 1 <= nums.length <= 104
// 	-104 <= nums[i] <= 104
// 	nums is sorted in a strictly increasing order.
//
// Helpful references (internal KB):
// - Balanced Search Trees (tree, ds, recursion)
//   • When to use: When needing a self-balancing search tree that guarantees logarithmic time complexity for search and insertion operations. Useful for maintaining data in sorted order with consistent performance, especially when frequent updates are expected.
//   • Idea: A 2-3 tree is a self-balancing search tree where every node has either two children (a 2-node) or three children (a 3-node), ensuring all leaves are at the same depth. It guarantees O(log N) time complexity for search, insertion, and deletion operations.
//   • Invariants: All leaves are at the same depth from the root.; Every node is either a 2-node (one key, two children) or a 3-node (two keys, three children).
//   • Tips: Understand the two node types: 2-nodes (one key, two children) and 3-nodes (two keys, three children).; Insertion always starts by finding the leaf position, then propagates splits upwards if a 4-node is formed.
//   • Pitfalls: Incorrectly handling the promotion of keys during node splits can break the tree's structure.; Forgetting to update parent links after a node split or merge operation.
// - Range Minimum Query (array, tree, divide-and-conquer)
//   • When to use: When needing to find the minimum (or maximum) value within various specified ranges of an array efficiently. Suitable for scenarios with many queries on a fixed or frequently updated dataset.
//   • Idea: This technique precomputes answers for subproblems, typically by building a tree-like structure or a table, to efficiently answer queries for the minimum (or maximum) value within a given range. It achieves O(log N) or O(1) query time after O(N log N) or O(N) preprocessing, depending on the specific data structure used.
//   • Invariants: For a Segment Tree node covering range [L, R], its value stores the minimum of all elements in the original array from index L to R.; For any query range [Q_L, Q_R], the combined result from relevant tree nodes correctly represents the minimum in [Q_L, Q_R].
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; For dynamic arrays with updates, Segment Tree offers O(log N) query and update time after O(N) preprocessing.
//   • Pitfalls: Off-by-one errors when defining range boundaries or calculating indices.; Incorrect merge logic for segment tree nodes (e.g., using sum instead of min).
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
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
 * @param {number[]} nums
 * @return {TreeNode}
 */
var sortedArrayToBST = function(nums) {
    if (nums.length === 0) return null;

    function buildBST(left, right) {
        if (left > right) return null;

        const mid = Math.floor((left + right) / 2);
        const node = new TreeNode(nums[mid]);

        node.left = buildBST(left, mid - 1);
        node.right = buildBST(mid + 1, right);

        return node;
    }

    return buildBST(0, nums.length - 1);
};  