// Source: https://leetcode.com/problems/remove-linked-list-elements/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
//
// Example:
// Input: head = [1,2,6,3,4,5,6], val = 6
// Output: [1,2,3,4,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 104].
// 	1 <= Node.val <= 50
// 	0 <= val <= 50
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    struct ListNode* current = dummy;

    while (current->next != NULL) {
        if (current->next->val == val) {
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    struct ListNode* newHead = dummy->next;
    free(dummy);
    return newHead;     
}
