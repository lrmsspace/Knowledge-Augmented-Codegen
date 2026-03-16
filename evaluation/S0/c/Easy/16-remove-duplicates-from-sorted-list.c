// Source: https://leetcode.com/problems/remove-duplicates-from-sorted-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.
//
// Example:
// Input: head = [1,1,2]
// Output: [1,2]
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
    struct ListNode* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->val == current->next->val) {
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;        
}
