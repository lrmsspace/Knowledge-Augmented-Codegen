// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.
//
// Example:
// Input: head = [1,2,3,3,4,4,5]
// Output: [1,2,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 300].
// 	-100 <= Node.val <= 100
// 	The list is guaranteed to be sorted in ascending order.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy; // Pointer to the node before the current sequence
    struct ListNode* curr = head;   // Pointer to the current node

    while (curr != NULL) {
        // Check if the current node has duplicates
        if (curr->next != NULL && curr->val == curr->next->val) {
            // Skip all nodes with the same value
            while (curr->next != NULL && curr->val == curr->next->val) {
                curr = curr->next;
            }
            // Link the previous node to the node after the duplicates
            prev->next = curr->next;
        } else {
            // No duplicates, move the prev pointer
            prev = prev->next;
        }
        // Move to the next node
        curr = curr->next;
    }

    return dummy.next;      
}
