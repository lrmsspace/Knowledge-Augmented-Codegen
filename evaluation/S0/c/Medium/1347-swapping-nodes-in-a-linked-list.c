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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapNodes(struct ListNode* head, int k) {
    struct ListNode *first = head, *second = head, *current = head;
    int count = 1;

    // Find the kth node from the beginning
    while (count < k) {
        first = first->next;
        count++;
    }

    struct ListNode *kthFromStart = first;

    // Continue traversing to find the kth node from the end
    while (current->next != NULL) {
        current = current->next;
        if (count >= k) {
            second = second->next;
        }
        count++;
    }

    // Swap the values of the two nodes
    int temp = kthFromStart->val;
    kthFromStart->val = second->val;
    second->val = temp;

    return head;        
}
