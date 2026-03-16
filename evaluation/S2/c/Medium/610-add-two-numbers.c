// Source: https://leetcode.com/problems/add-two-numbers/   |   Difficulty: Medium
//
// Problem Description:
// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Example:
// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
// Explanation: 342 + 465 = 807.
//
// Constraints:
// The number of nodes in each linked list is in the range [1, 100].
// 	0 <= Node.val <= 9
// 	It is guaranteed that the list represents a number that does not have leading zeros.
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
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyHead->val = 0;
    dummyHead->next = NULL;
    
    struct ListNode* p = l1;
    struct ListNode* q = l2;
    struct ListNode* current = dummyHead;
    
    int carry = 0;
    
    while (p != NULL || q != NULL) {
        int x = (p != NULL) ? p->val : 0;
        int y = (q != NULL) ? q->val : 0;
        
        int sum = carry + x + y;
        carry = sum / 10;
        
        current->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        current->next->val = sum % 10;
        current->next->next = NULL;
        
        current = current->next;
        
        if (p != NULL) p = p->next;
        if (q != NULL) q = q->next;
    }
    
    if (carry > 0) {
        current->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        current->next->val = carry;
        current->next->next = NULL;
    }
    
    struct ListNode* result = dummyHead->next;
    free(dummyHead);
    
    return result;      
}
