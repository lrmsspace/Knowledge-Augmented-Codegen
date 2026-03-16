// Source: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.
//
// Example:
// Input: nums = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
// Explanation: [0,-10,5,null,-3,null,9] is also accepted:
//
// Constraints:
// 1 <= nums.length <= 104
// 	-104 <= nums[i] <= 104
// 	nums is sorted in a strictly increasing order.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    if (numsSize == 0) {
        return NULL;
    }

    int mid = numsSize / 2;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
    root->left = sortedArrayToBST(nums, mid);
    root->right = sortedArrayToBST(nums + mid + 1, numsSize - mid - 1);

    return root;        
}
