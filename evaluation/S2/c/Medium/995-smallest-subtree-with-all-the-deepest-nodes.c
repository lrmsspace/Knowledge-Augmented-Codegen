// Source: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the depth of each node is the shortest distance to the root.
//
// Return the smallest subtree such that it contains all the deepest nodes in the original tree.
//
// A node is called the deepest if it has the largest depth possible among any node in the entire tree.
//
// The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.
//
// Example:
// Input: root = [3,5,1,6,2,0,8,null,null,7,4]
// Output: [2,7,4]
// Explanation: We return the node with value 2, colored in yellow in the diagram.
// The nodes coloured in blue are the deepest nodes of the tree.
// Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.
//
// Constraints:
// The number of nodes in the tree will be in the range [1, 500].
// 	0 <= Node.val <= 500
// 	The values of the nodes in the tree are unique.
//
//
//  
// Note: This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
//
// Helpful references (internal KB):
// - N/A
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
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    if (!root) return NULL;
    
    struct TreeNode *left = subtreeWithAllDeepest(root->left);
    struct TreeNode *right = subtreeWithAllDeepest(root->right);
    
    if (!left) return right;
    if (!right) return left;
    
    return root;        
}
