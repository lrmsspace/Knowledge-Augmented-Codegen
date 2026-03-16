// Source: https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary search tree and an array queries of size n consisting of positive integers.
//
// Find a 2D array answer of size n where answer[i] = [mini, maxi]:
//
//
// 	mini is the largest value in the tree that is smaller than or equal to queries[i]. If a such value does not exist, add -1 instead.
// 	maxi is the smallest value in the tree that is greater than or equal to queries[i]. If a such value does not exist, add -1 instead.
//
//
// Return the array answer.
//
// Example:
// Input: root = [6,2,13,1,4,9,15,null,null,null,null,null,null,14], queries = [2,5,16]
// Output: [[2,2],[4,6],[15,-1]]
// Explanation: We answer the queries in the following way:
// - The largest number that is smaller or equal than 2 in the tree is 2, and the smallest number that is greater or equal than 2 is still 2. So the answer for the first query is [2,2].
// - The largest number that is smaller or equal than 5 in the tree is 4, and the smallest number that is greater or equal than 5 is 6. So the answer for the second query is [4,6].
// - The largest number that is smaller or equal than 16 in the tree is 15, and the smallest number that is greater or equal than 16 does not exist. So the answer for the third query is [15,-1].
//
// Constraints:
// The number of nodes in the tree is in the range [2, 105].
// 	1 <= Node.val <= 106
// 	n == queries.length
// 	1 <= n <= 105
// 	1 <= queries[i] <= 106
//
// Helpful references (internal KB):
// - Binary Search Trees
//  (tree, recursion)
//   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
//   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
//   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
//   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
// - Binary Search Trees
//  (tree, enumeration)
//   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
//   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
//   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
//   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public List<List<Integer>> closestNodes(TreeNode root, List<Integer> queries) {
        List<List<Integer>> ans = new ArrayList<>();
        for (int q : queries) {
            int[] res = search(root, q);
            ans.add(Arrays.asList(res[0], res[1]));
        }
        return ans;         
    }
}
