// Source: https://leetcode.com/problems/rotate-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, rotate the list to the right by k places.
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
//
// Constraints:
// The number of nodes in the list is in the range [0, 500].
// 	-100 <= Node.val <= 100
// 	0 <= k <= 2 * 109
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || !head->next || k == 0) {
        return head;
    }

    // Compute the length of the list and get the tail node
    struct ListNode* tail = head;
    int length = 1;
    while (tail->next) {
        tail = tail->next;
        length++;
    }

    // Make the list circular
    tail->next = head;

    // Find the new tail: (length - k % length - 1)th node
    // and the new head: (length - k % length)th node
    k = k % length;
    int stepsToNewHead = length - k;
    struct ListNode* newTail = head;
    for (int i = 1; i < stepsToNewHead; i++) {
        newTail = newTail->next;
    }
    struct ListNode* newHead = newTail->next;

    // Break the circle
    newTail->next = NULL;

    return newHead;     
}
