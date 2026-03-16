// Source: https://leetcode.com/problems/reverse-linked-list-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.
//
// Example:
// Input: head = [1,2,3,4,5], left = 2, right = 4
// Output: [1,4,3,2,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= n <= 500
// 	-500 <= Node.val <= 500
// 	1 <= left <= right <= n
//
//
//  
// Follow up: Could you do it in one pass?
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
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    if (head == NULL || left == right) {
        return head;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;

    // Move prev to the node before the left position
    for (int i = 1; i < left; i++) {
        prev = prev->next;
    }

    struct ListNode* const reverse_start = prev->next;
    struct ListNode* curr = reverse_start->next;

    // Reverse the sublist from left to right
    for (int i = 0; i < right - left; i++) {
        reverse_start->next = curr->next;
        curr->next = prev->next;
        prev->next = curr;
        curr = reverse_start->next;
    }

    return dummy.next;      
}
