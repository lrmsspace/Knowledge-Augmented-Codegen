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
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return new TreeNode(head->val);

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;

        // Find the middle node using slow and fast pointers
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // Disconnect the left half from the middle
        if (prev) {
            prev->next = nullptr;
        }

        TreeNode* root = new TreeNode(slow->val);
        // If slow is head, it means there is no left subtree
        if (slow != head) {
            root->left = sortedListToBST(head);
        }
        root->right = sortedListToBST(slow->next);

        return root;            
    }
};
