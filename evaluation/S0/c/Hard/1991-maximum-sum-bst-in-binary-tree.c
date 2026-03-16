// Source: https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
//
// Assume a BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys less than the node's key.
// 	The right subtree of a node contains only nodes with keys greater than the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
// Output: 20
// Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 4 * 104].
// 	-4 * 104 <= Node.val <= 4 * 104
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxSumBST(struct TreeNode* root) {
    int maxSum = 0;

    struct Info {
        int isBST;
        int minVal;
        int maxVal;
        int sum;
    };

    struct Info dfs(struct TreeNode* node) {
        if (!node) {
            struct Info info = {1, 2147483647, -2147483648, 0};
            return info;
        }

        struct Info leftInfo = dfs(node->left);
        struct Info rightInfo = dfs(node->right);

        struct Info currInfo;
        if (leftInfo.isBST && rightInfo.isBST &&
            node->val > leftInfo.maxVal && node->val < rightInfo.minVal) {
            currInfo.isBST = 1;
            currInfo.sum = leftInfo.sum + rightInfo.sum + node->val;
            currInfo.minVal = (node->left) ? leftInfo.minVal : node->val;
            currInfo.maxVal = (node->right) ? rightInfo.maxVal : node->val;

            if (currInfo.sum > maxSum) {
                maxSum = currInfo.sum;
            }
        } else {
            currInfo.isBST = 0;
            currInfo.sum = 0; // Not a BST, sum is irrelevant
            currInfo.minVal = 0; // Irrelevant
            currInfo.maxVal = 0; // Irrelevant
        }

        return currInfo;
    }

    dfs(root);
    return maxSum;      
}
