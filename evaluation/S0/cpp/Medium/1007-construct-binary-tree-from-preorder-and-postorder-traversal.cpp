// Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a binary tree of distinct values and postorder is the postorder traversal of the same tree, reconstruct and return the binary tree.
//
// If there exist multiple answers, you can return any of them.
//
// Example:
// Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
// Output: [1,2,3,4,5,6,7]
//
// Constraints:
// 1 <= preorder.length <= 30
// 	1 <= preorder[i] <= preorder.length
// 	All the values of preorder are unique.
// 	postorder.length == preorder.length
// 	1 <= postorder[i] <= postorder.length
// 	All the values of postorder are unique.
// 	It is guaranteed that preorder and postorder are the preorder traversal and postorder traversal of the same binary tree.
//

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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        if (preorder.empty() || postorder.empty()) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[0]);
        if (preorder.size() == 1) {
            return root;
        }

        int leftRootVal = preorder[1];
        int leftSubtreeSize = 0;
        for (int i = 0; i < postorder.size(); ++i) {
            if (postorder[i] == leftRootVal) {
                leftSubtreeSize = i + 1;
                break;
            }
        }

        vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + 1 + leftSubtreeSize);
        vector<int> rightPreorder(preorder.begin() + 1 + leftSubtreeSize, preorder.end());
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftSubtreeSize);
        vector<int> rightPostorder(postorder.begin() + leftSubtreeSize, postorder.end() - 1);

        root->left = constructFromPrePost(leftPreorder, leftPostorder);
        root->right = constructFromPrePost(rightPreorder, rightPostorder);

        return root;            
    }
};
