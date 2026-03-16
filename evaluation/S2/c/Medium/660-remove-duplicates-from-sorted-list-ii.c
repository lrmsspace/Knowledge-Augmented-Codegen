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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;
    struct ListNode* current = head;

    while (current != NULL) {
        // Check for duplicates
        while (current->next != NULL && current->val == current->next->val) {
            current = current->next; // Skip duplicate nodes
        }

        if (prev->next == current) {
            // No duplicates, move prev pointer
            prev = prev->next;
        } else {
            // Duplicates found, skip them
            prev->next = current->next;
        }

        current = current->next; // Move to the next node
    }

    return dummy.next; // Return the head of the modified list      
}
