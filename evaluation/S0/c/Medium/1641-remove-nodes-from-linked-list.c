// Source: https://leetcode.com/problems/remove-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list.
//
// Remove every node which has a node with a greater value anywhere to the right side of it.
//
// Return the head of the modified linked list.
//
// Example:
// Input: head = [5,2,13,3,8]
// Output: [13,8]
// Explanation: The nodes that should be removed are 5, 2 and 3.
// - Node 13 is to the right of node 5.
// - Node 13 is to the right of node 2.
// - Node 8 is to the right of node 3.
//
// Constraints:
// The number of the nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNodes(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    struct ListNode* next = NULL;

    // Reverse the linked list
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;

    // Remove nodes that have a greater value to the left (originally to the right)
    struct ListNode* maxNode = head;
    curr = head;
    prev = NULL;

    while (curr != NULL) {
        if (curr->val >= maxNode->val) {
            maxNode = curr;
            prev = curr;
            curr = curr->next;
        } else {
            prev->next = curr->next;
            curr = prev->next;
        }
    }

    // Reverse the linked list back to original order
    prev = NULL;
    curr = head;
    next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;

    return head;        
}
