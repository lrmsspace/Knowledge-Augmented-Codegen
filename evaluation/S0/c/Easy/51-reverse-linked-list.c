// Source: https://leetcode.com/problems/reverse-linked-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a singly linked list, reverse the list, and return the reversed list.
//
// Example:
// Input: head = [1,2,3,4,5]
// Output: [5,4,3,2,1]
//
// Constraints:
// The number of nodes in the list is the range [0, 5000].
// 	-5000 <= Node.val <= 5000
//
//
//  
// Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    struct ListNode* next = NULL;

    while (curr != NULL) {
        next = curr->next;  // Store next node
        curr->next = prev;  // Reverse current node's pointer
        prev = curr;        // Move pointers one position ahead
        curr = next;
    }

    return prev;  // New head of the reversed list      
}
