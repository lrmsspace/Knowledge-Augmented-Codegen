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
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxSumBST(TreeNode* root) {
        int maxSum = 0;
        
        // Returns {isBST, minVal, maxVal, sum}
        function<tuple<bool, int, int, int>(TreeNode*)> dfs = [&](TreeNode* node) -> tuple<bool, int, int, int> {
            if (!node) {
                return {true, INT_MAX, INT_MIN, 0};
            }
            
            auto [isLeftBST, leftMin, leftMax, leftSum] = dfs(node->left);
            auto [isRightBST, rightMin, rightMax, rightSum] = dfs(node->right);
            
            if (isLeftBST && isRightBST && node->val > leftMax && node->val < rightMin) {
                int currSum = leftSum + rightSum + node->val;
                maxSum = max(maxSum, currSum);
                int currMin = min(leftMin, node->val);
                int currMax = max(rightMax, node->val);
                return {true, currMin, currMax, currSum};
            } else {
                return {false, 0, 0, 0};
            }
        };
        
        dfs(root);
        return maxSum;          
    }
};
