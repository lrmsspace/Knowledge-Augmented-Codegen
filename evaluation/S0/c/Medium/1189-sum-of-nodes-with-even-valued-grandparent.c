// Source: https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the sum of values of nodes with an even-valued grandparent. If there are no nodes with an even-valued grandparent, return 0.
//
// A grandparent of a node is the parent of its parent if it exists.
//
// Example:
// Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
// Output: 18
// Explanation: The red nodes are the nodes with even-value grandparent while the blue nodes are the even-value grandparents.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 100
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int sumEvenGrandparent(struct TreeNode* root) {
    if (!root) return 0;

    int sum = 0;

    if (root->val % 2 == 0) {
        if (root->left) {
            if (root->left->left) sum += root->left->left->val;
            if (root->left->right) sum += root->left->right->val;
        }
        if (root->right) {
            if (root->right->left) sum += root->right->left->val;
            if (root->right->right) sum += root->right->right->val;
        }
    }

    sum += sumEvenGrandparent(root->left);
    sum += sumEvenGrandparent(root->right);

    return sum;     
}
