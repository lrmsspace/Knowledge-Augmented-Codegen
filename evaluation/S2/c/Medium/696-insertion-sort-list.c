// Source: https://leetcode.com/problems/insertion-sort-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list, sort the list using insertion sort, and return the sorted list's head.
//
// The steps of the insertion sort algorithm:
//
//
// 	Insertion sort iterates, consuming one input element each repetition and growing a sorted output list.
// 	At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list and inserts it there.
// 	It repeats until no input elements remain.
//
//
// The following is a graphical example of the insertion sort algorithm. The partially sorted list (black) initially contains only the first element in the list. One element (red) is removed from the input data and inserted in-place into the sorted list with each iteration.
//
// Example:
// Input: head = [4,2,1,3]
// Output: [1,2,3,4]
//
// Constraints:
// The number of nodes in the list is in the range [1, 5000].
// 	-5000 <= Node.val <= 5000
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
struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* lastSorted = head;
    struct ListNode* curr = head->next;

    while (curr != NULL) {
        if (lastSorted->val <= curr->val) {
            lastSorted = lastSorted->next;
        } else {
            struct ListNode* prev = &dummy;
            while (prev->next->val <= curr->val) {
                prev = prev->next;
            }
            lastSorted->next = curr->next;
            curr->next = prev->next;
            prev->next = curr;
        }
        curr = lastSorted->next;
    }

    return dummy.next;      
}
