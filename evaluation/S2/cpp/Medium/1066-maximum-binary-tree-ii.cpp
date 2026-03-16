// Source: https://leetcode.com/problems/maximum-binary-tree-ii/   |   Difficulty: Medium
//
// Problem Description:
// A maximum tree is a tree where every node has a value greater than any other value in its subtree.
//
// You are given the root of a maximum binary tree and an integer val.
//
// Just as in the previous problem, the given tree was constructed from a list a (root = Construct(a)) recursively with the following Construct(a) routine:
//
//
// 	If a is empty, return null.
// 	Otherwise, let a[i] be the largest element of a. Create a root node with the value a[i].
// 	The left child of root will be Construct([a[0], a[1], ..., a[i - 1]]).
// 	The right child of root will be Construct([a[i + 1], a[i + 2], ..., a[a.length - 1]]).
// 	Return root.
//
//
// Note that we were not given a directly, only a root node root = Construct(a).
//
// Suppose b is a copy of a with the value val appended to it. It is guaranteed that b has unique values.
//
// Return Construct(b).
//
// Example:
// Input: root = [4,1,3,null,null,2], val = 5
// Output: [5,4,null,1,3,null,null,2]
// Explanation: a = [1,4,2,3], b = [1,4,2,3,5]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	1 <= Node.val <= 100
// 	All the values of the tree are unique.
// 	1 <= val <= 100
//
// Helpful references (internal KB):
// - Treap (Cartesian tree) (tree, recursion, binary-search)
//   • When to use: When you need a self-balancing binary search tree that supports efficient split and merge operations, often used for dynamic set management or range queries on mutable data.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on priorities (randomly assigned). It supports efficient operations like split and merge, typically with an average time complexity of O(log N).
//   • Invariants: For any node, its key is greater than or equal to all keys in its left subtree.; For any node, its key is less than all keys in its right subtree.
//   • Tips: Understand the recursive nature of Split and Merge operations.; Randomly assign priorities (Y values) to ensure probabilistic balancing.
//   • Pitfalls: Incorrect handling of null pointers or empty subtrees in recursion.; Forgetting to update parent pointers or root pointers after operations.
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use when you need to represent all positive irreducible fractions in a structured tree or efficiently search for a specific fraction. It's also useful for generating Farey sequences or understanding rational number properties.
//   • Idea: The Stern-Brocot tree is an infinite binary tree containing every positive irreducible fraction exactly once, ordered by value. Searching for a fraction or generating parts of the tree typically involves a logarithmic number of steps relative to the sum of the numerator and denominator, making it efficient for O(log(x+y)) operations.
//   • Invariants: For any node m/n, all fractions in its left subtree are strictly less than m/n.; For any node m/n, all fractions in its right subtree are strictly greater than m/n.
//   • Tips: The mediant of a/b and c/d is (a+c)/(b+d), which is always irreducible if a/b and c/d are.; All fractions in the Stern-Brocot tree are inherently irreducible.
//   • Pitfalls: Integer overflow when calculating mediants if numerators or denominators are very large.; Incorrectly handling the initial 'infinite' fractions (0/1 and 1/0) as boundary conditions.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);
        if (val > root->val) {
            TreeNode* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        root->right = insertIntoMaxTree(root->right, val);
        return root;            
    }
};
