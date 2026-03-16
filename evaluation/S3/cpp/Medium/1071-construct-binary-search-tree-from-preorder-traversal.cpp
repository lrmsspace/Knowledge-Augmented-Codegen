// Source: https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.
//
// It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.
//
// A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, and any descendant of Node.right has a value strictly greater than Node.val.
//
// A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.
//
// Example:
// Input: preorder = [8,5,1,7,10,12]
// Output: [8,5,10,1,7,null,12]
//
// Constraints:
// 1 <= preorder.length <= 100
// 	1 <= preorder[i] <= 1000
// 	All the values of preorder are unique.
//
// Helpful references (internal KB):
// - Binary Search Trees
//  (tree, recursion)
//   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
//   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
//   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
//   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
// - Treap (Cartesian tree) (tree, array, divide-and-conquer, recursion)
//   • When to use: Use when a dynamic data structure is needed to support efficient array-like operations (insert, delete, range queries/updates) on an ordered sequence, especially with frequent modifications at arbitrary positions.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on randomly assigned priorities. It supports various dynamic array operations and range queries/updates in expected O(log N) time.
//   • Invariants: For any node, its key is greater than all keys in its left subtree and less than all keys in its right subtree.; For any node, its priority is greater than or equal to the priorities of its children.
//   • Tips: Use random priorities to ensure probabilistic balance, avoiding worst-case O(N) operations.; Implement `split` and `merge` as fundamental building blocks for all other operations.
//   • Pitfalls: Forgetting to push lazy tags before accessing children or performing splits/merges.; Incorrectly updating `cnt` or aggregate fields after tree modifications.
// - Treap (Cartesian tree) (tree, recursion, binary-search)
//   • When to use: When you need a self-balancing binary search tree that supports efficient split and merge operations, often used for dynamic set management or range queries on mutable data.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on priorities (randomly assigned). It supports efficient operations like split and merge, typically with an average time complexity of O(log N).
//   • Invariants: For any node, its key is greater than or equal to all keys in its left subtree.; For any node, its key is less than all keys in its right subtree.
//   • Tips: Understand the recursive nature of Split and Merge operations.; Randomly assign priorities (Y values) to ensure probabilistic balancing.
//   • Pitfalls: Incorrect handling of null pointers or empty subtrees in recursion.; Forgetting to update parent pointers or root pointers after operations.
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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if (preorder.empty()) {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> nodeStack;
        nodeStack.push(root);
        
        for (size_t i = 1; i < preorder.size(); ++i) {
            TreeNode* node = new TreeNode(preorder[i]);
            if (preorder[i] < nodeStack.top()->val) {
                nodeStack.top()->left = node;
            } else {
                TreeNode* parent = nullptr;
                while (!nodeStack.empty() && preorder[i] > nodeStack.top()->val) {
                    parent = nodeStack.top();
                    nodeStack.pop();
                }
                parent->right = node;
            }
            nodeStack.push(node);
        }
        
        return root;            
    }
};
