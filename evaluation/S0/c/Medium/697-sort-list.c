// Source: https://leetcode.com/problems/sort-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, return the list after sorting it in ascending order.
//
// Example:
// Input: head = [4,2,1,3]
// Output: [1,2,3,4]
//
// Constraints:
// The number of nodes in the list is in the range [0, 5 * 104].
// 	-105 <= Node.val <= 105
//
//
//  
// Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* sortList(struct ListNode* head) {
    if (!head || !head->next) return head;

    // Find the middle point using the slow and fast pointer technique
    struct ListNode *slow = head, *fast = head, *prev = NULL;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = NULL; // Split the list into two halves

    // Recursively sort both halves
    struct ListNode* l1 = sortList(head);
    struct ListNode* l2 = sortList(slow);

    // Merge the two sorted halves
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2; // Append the remaining nodes

    return dummy.next;      
}
