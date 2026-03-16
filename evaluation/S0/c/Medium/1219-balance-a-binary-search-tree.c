// Source: https://leetcode.com/problems/balance-a-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.
//
// A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.
//
// Example:
// Input: root = [1,null,2,null,3,null,4,null,null]
// Output: [2,1,3,null,null,null,4]
// Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 105
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* balanceBST(struct TreeNode* root) {
    // Helper function to perform in-order traversal and store values in an array
    void inorderTraversal(struct TreeNode* node, int* arr, int* index) {
        if (!node) return;
        inorderTraversal(node->left, arr, index);
        arr[(*index)++] = node->val;
        inorderTraversal(node->right, arr, index);
    }

    // Helper function to build a balanced BST from sorted array
    struct TreeNode* buildBalancedBST(int* arr, int start, int end) {
        if (start > end) return NULL;
        int mid = start + (end - start) / 2;
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = arr[mid];
        node->left = buildBalancedBST(arr, start, mid - 1);
        node->right = buildBalancedBST(arr, mid + 1, end);
        return node;
    }

    // Step 1: Store the values of the BST in sorted order
    int values[10000]; // Assuming maximum number of nodes is 10^4
    int index = 0;
    inorderTraversal(root, values, &index);

    // Step 2: Build a balanced BST from the sorted values
    return buildBalancedBST(values, 0, index - 1);      
}
