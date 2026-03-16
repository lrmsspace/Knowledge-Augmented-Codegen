// Source: https://leetcode.com/problems/binary-tree-cameras/   |   Difficulty: Hard
//
// Problem Description:
// You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.
//
// Return the minimum number of cameras needed to monitor all nodes of the tree.
//
// Example:
// Input: root = [0,0,null,0,0]
// Output: 1
// Explanation: One camera is enough to monitor all nodes if placed as shown.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	Node.val == 0
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minCameraCover(struct TreeNode* root) {
    enum { NOT_COVERED = 0, COVERED_NO_CAM = 1, HAS_CAM = 2 };

    int res = 0;

    int dfs(struct TreeNode *node) {
        if (!node) return COVERED_NO_CAM;

        int leftState = dfs(node->left);
        int rightState = dfs(node->right);

        if (leftState == NOT_COVERED || rightState == NOT_COVERED) {
            res++;
            return HAS_CAM;
        }

        if (leftState == HAS_CAM || rightState == HAS_CAM) {
            return COVERED_NO_CAM;
        }

        return NOT_COVERED;
    }

    if (dfs(root) == NOT_COVERED) {
        res++;
    }

    return res;     
}
