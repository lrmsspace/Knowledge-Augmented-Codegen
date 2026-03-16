// Source: https://leetcode.com/problems/partition-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//
// You should preserve the original relative order of the nodes in each of the two partitions.
//
// Example:
// Input: head = [1,4,3,2,5,2], x = 3
// Output: [1,2,2,4,3,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 200].
// 	-100 <= Node.val <= 100
// 	-200 <= x <= 200
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode lessHead = {0, NULL};
    struct ListNode greaterHead = {0, NULL};
    struct ListNode* lessTail = &lessHead;
    struct ListNode* greaterTail = &greaterHead;
    struct ListNode* current = head;

    while (current != NULL) {
        if (current->val < x) {
            lessTail->next = current;
            lessTail = lessTail->next;
        } else {
            greaterTail->next = current;
            greaterTail = greaterTail->next;
        }
        current = current->next;
    }

    greaterTail->next = NULL; // Important to avoid cycle in linked list
    lessTail->next = greaterHead.next; // Connect the two partitions

    return lessHead.next;       
}
