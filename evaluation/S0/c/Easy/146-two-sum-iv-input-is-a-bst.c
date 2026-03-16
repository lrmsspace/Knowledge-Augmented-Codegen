// Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.
//
// Example:
// Input: root = [5,3,6,2,4,null,7], k = 9
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-104 <= Node.val <= 104
// 	root is guaranteed to be a valid binary search tree.
// 	-105 <= k <= 105
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool findTarget(struct TreeNode* root, int k) {
    #define MAX_NODES 10000
    int values[MAX_NODES];
    int count = 0;

    // In-order traversal to get sorted values from BST
    void inorder(struct TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        values[count++] = node->val;
        inorder(node->right);
    }

    inorder(root);

    // Two-pointer technique to find if two numbers sum to k
    int left = 0, right = count - 1;
    while (left < right) {
        int sum = values[left] + values[right];
        if (sum == k) {
            return true;
        } else if (sum < k) {
            left++;
        } else {
            right--;
        }
    }

    return false;       
}
