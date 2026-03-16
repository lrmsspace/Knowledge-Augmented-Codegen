// Source: https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list where elements are sorted in ascending order, convert it to a height-balanced binary search tree.
//
// Example:
// Input: head = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
// Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
//
// Constraints:
// The number of nodes in head is in the range [0, 2 * 104].
// 	-105 <= Node.val <= 105
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (!head) return NULL;
    if (!head->next) {
        struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = head->val;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    struct ListNode *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (prev) prev->next = NULL;

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = slow->val;
    root->left = sortedListToBST(head == slow ? NULL : head);
    root->right = sortedListToBST(slow->next);

    return root;        
}
