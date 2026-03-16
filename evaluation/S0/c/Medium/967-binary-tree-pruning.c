// Source: https://leetcode.com/problems/binary-tree-pruning/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
//
// A subtree of a node node is node plus every node that is a descendant of node.
//
// Example:
// Input: root = [1,null,0,0,1]
// Output: [1,null,0,null,1]
// Explanation: 
// Only the red nodes satisfy the property "every subtree not containing a 1".
// The diagram on the right represents the answer.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 200].
// 	Node.val is either 0 or 1.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* pruneTree(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);
    
    if (root->val == 0 && root->left == NULL && root->right == NULL) {
        return NULL;
    }
    
    return root;        
}
