// Source: https://leetcode.com/problems/linked-list-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree root and a linked list with head as the first node. 
//
// Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
//
// In this context downward path means a path that starts at some node and goes downwards.
//
// Example:
// Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
// Output: true
// Explanation: Nodes in blue form a subpath in the binary Tree.
//
// Constraints:
// The number of nodes in the tree will be in the range [1, 2500].
// 	The number of nodes in the list will be in the range [1, 100].
// 	1 <= Node.val <= 100 for each node in the linked list and binary tree.
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
bool isSubPath(struct ListNode* head, struct TreeNode* root) {
    if (!head)
        return true;
    if (!root)
        return false;

    if (root->val == head->val) {
        struct ListNode* next = head->next;
        struct TreeNode* left = root->left;
        struct TreeNode* right = root->right;

        if (!next)
            return true;

        bool left_match = false, right_match = false;

        if (left)
            left_match = isSubPath(next, left);
        if (right)
            right_match = isSubPath(next, right);

        if (left_match || right_match)
            return true;
    }

    return isSubPath(head, root->left) || isSubPath(head, root->right);     
}
