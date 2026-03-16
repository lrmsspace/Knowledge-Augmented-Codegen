// Source: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
//
// Return the head of the linked list after doubling it.
//
// Example:
// Input: head = [1,8,9]
// Output: [3,7,8]
// Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
//
// Constraints:
// The number of nodes in the list is in the range [1, 104]
// 	0 <= Node.val <= 9
// 	The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* doubleIt(struct ListNode* head) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0;
    dummy->next = head;

    struct ListNode* slow = dummy;
    struct ListNode* fast = dummy;

    // Find the last node where value is less than 5
    while (fast->next != NULL) {
        fast = fast->next;
        if (fast->val < 5) {
            slow = fast;
        }
    }

    // Double the last node
    fast->val *= 2;

    // Handle carry if needed
    if (fast->val >= 10) {
        fast->val -= 10;
        slow->val += 1;

        // Propagate carry backwards if needed
        struct ListNode* curr = slow;
        while (curr != dummy) {
            if (curr->val >= 10) {
                curr->val -= 10;
                if (curr == dummy) {
                    // Create a new head if dummy needs to carry over
                    struct ListNode* newHead = (struct ListNode*)malloc(sizeof(struct ListNode));
                    newHead->val = 1;
                    newHead->next = dummy->next;
                    free(dummy);
                    return newHead;
                } else {
                    // Find previous node
                    struct ListNode* prev = dummy;
                    while (prev->next != curr) {
                        prev = prev->next;
                    }
                    prev->val += 1;
                }
            }
            curr = dummy; // Move to previous node
            while (curr->next != slow && curr->next != NULL) {
                curr = curr->next;
            }
            slow = curr;
        }
    }

    struct ListNode* result = dummy->next;
    free(dummy);
    return result;      
}
