// Source: https://leetcode.com/problems/range-sum-of-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].
//
// Example:
// Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
// Output: 32
// Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 2 * 104].
// 	1 <= Node.val <= 105
// 	1 <= low <= high <= 105
// 	All Node.val are unique.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int rangeSumBST(struct TreeNode* root, int low, int high) {
    if (root == NULL) {
        return 0;
    }
    
    int sum = 0;
    
    if (root->val >= low && root->val <= high) {
        sum += root->val;
    }
    
    if (root->val > low) {
        sum += rangeSumBST(root->left, low, high);
    }
    
    if (root->val < high) {
        sum += rangeSumBST(root->right, low, high);
    }
    
    return sum;     
}
