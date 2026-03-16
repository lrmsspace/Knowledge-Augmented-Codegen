// Source: https://leetcode.com/problems/reverse-nodes-in-k-group/   |   Difficulty: Hard
//
// Problem Description:
// Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
//
// k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
//
// You may not alter the values in the list's nodes, only nodes themselves may be changed.
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [2,1,4,3,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= k <= n <= 5000
// 	0 <= Node.val <= 1000
//
//
//  
// Follow-up: Can you solve the problem in O(1) extra memory space?
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prevGroupEnd = &dummy;

    while (1) {
        struct ListNode *kthNode = prevGroupEnd;
        for (int i = 0; i < k; ++i) {
            kthNode = kthNode->next;
            if (!kthNode) {
                return dummy.next; // Not enough nodes to reverse
            }
        }

        struct ListNode *groupStart = prevGroupEnd->next;
        struct ListNode *nextGroupStart = kthNode->next;

        // Reverse the k nodes
        struct ListNode *prev = nextGroupStart;
        struct ListNode *curr = groupStart;
        while (curr != nextGroupStart) {
            struct ListNode *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        // Connect with the previous part
        prevGroupEnd->next = kthNode;
        prevGroupEnd = groupStart; // Move to the end of the reversed group
    }       
}
