// Source: https://leetcode.com/problems/maximum-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums with no duplicates. A maximum binary tree can be built recursively from nums using the following algorithm:
//
//
// 	Create a root node whose value is the maximum value in nums.
// 	Recursively build the left subtree on the subarray prefix to the left of the maximum value.
// 	Recursively build the right subtree on the subarray suffix to the right of the maximum value.
//
//
// Return the maximum binary tree built from nums.
//
// Example:
// Input: nums = [3,2,1,6,0,5]
// Output: [6,3,5,null,2,0,null,null,1]
// Explanation: The recursive calls are as follow:
// - The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
//     - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
//         - Empty array, so no child.
//         - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
//             - Empty array, so no child.
//             - Only one element, so child is a node with value 1.
//     - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
//         - Only one element, so child is a node with value 0.
//         - Empty array, so no child.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] <= 1000
// 	All integers in nums are unique.
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Treap (Cartesian tree) (tree, recursion, binary-search)
//   • When to use: When you need a self-balancing binary search tree that supports efficient split and merge operations, often used for dynamic set management or range queries on mutable data.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on priorities (randomly assigned). It supports efficient operations like split and merge, typically with an average time complexity of O(log N).
//   • Invariants: For any node, its key is greater than or equal to all keys in its left subtree.; For any node, its key is less than all keys in its right subtree.
//   • Tips: Understand the recursive nature of Split and Merge operations.; Randomly assign priorities (Y values) to ensure probabilistic balancing.
//   • Pitfalls: Incorrect handling of null pointers or empty subtrees in recursion.; Forgetting to update parent pointers or root pointers after operations.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize) {
    if (numsSize == 0) {
        return NULL;
    }

    // Find the index of the maximum value in the current array segment
    int maxIndex = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }

    // Create a new TreeNode with the maximum value
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = nums[maxIndex];
    node->left = NULL;
    node->right = NULL;

    // Recursively construct the left and right subtrees
    node->left = constructMaximumBinaryTree(nums, maxIndex); // Left subarray
    node->right = constructMaximumBinaryTree(nums + maxIndex + 1, numsSize - maxIndex - 1); // Right subarray

    return node;        
}
