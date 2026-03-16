// Source: https://leetcode.com/problems/swapping-nodes-in-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list, and an integer k.
//
// Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [1,4,3,2,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= k <= n <= 105
// 	0 <= Node.val <= 100
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
struct ListNode* swapNodes(struct ListNode* head, int k) {
    struct ListNode *first = head, *second = head, *current = head;
    int i = 1;

    while (current != NULL) {
        if (i == k) {
            first = current;
        }
        if (i > k) {
            second = second->next;
        }
        current = current->next;
        i++;
    }

    // Swap values of the two nodes
    int temp = first->val;
    first->val = second->val;
    second->val = temp;

    return head;        
}
