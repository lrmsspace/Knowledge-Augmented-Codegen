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
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minCameraCover(TreeNode* root) {
        int cameras = 0;
        
        // States:
        // 0 - not covered
        // 1 - has camera
        // 2 - covered
        
        function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
            if (!node) return 2;  // null nodes are considered covered
            
            int leftState = dfs(node->left);
            int rightState = dfs(node->right);
            
            if (leftState == 0 || rightState == 0) {
                cameras++;
                return 1;  // place camera here
            }
            
            if (leftState == 1 || rightState == 1) {
                return 2;  // covered
            }
            
            return 0;  // not covered
        };
        
        if (dfs(root) == 0) {
            cameras++;
        }
        
        return cameras;         
    }
};
