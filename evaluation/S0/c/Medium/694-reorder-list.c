// Source: https://leetcode.com/problems/reorder-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a singly linked-list. The list can be represented as:
//
//
// L0 → L1 → … → Ln - 1 → Ln
//
//
// Reorder the list to be on the following form:
//
//
// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
//
//
// You may not modify the values in the list's nodes. Only nodes themselves may be changed.
//
// Example:
// Input: head = [1,2,3,4]
// Output: [1,4,2,3]
//
// Constraints:
// The number of nodes in the list is in the range [1, 5 * 104].
// 	1 <= Node.val <= 1000
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void reorderList(struct ListNode* head) {
    if (!head || !head->next || !head->next->next) return;

    // Step 1: Find the middle of the linked list
    struct ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse the second half of the linked list
    struct ListNode *prev = NULL, *curr = slow, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Step 3: Merge the two halves
    struct ListNode *first = head, *second = prev;
    while (second->next) {
        struct ListNode *temp1 = first->next;
        struct ListNode *temp2 = second->next;

        first->next = second;
        second->next = temp1;

        first = temp1;
        second = temp2;
    }       
}
