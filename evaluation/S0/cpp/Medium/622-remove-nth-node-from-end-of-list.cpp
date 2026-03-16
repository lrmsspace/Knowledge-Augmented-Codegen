// Source: https://leetcode.com/problems/remove-nth-node-from-end-of-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
// Example:
// Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
//
// Constraints:
// The number of nodes in the list is sz.
// 	1 <= sz <= 30
// 	0 <= Node.val <= 100
// 	1 <= n <= sz
//
//
//  
// Follow up: Could you do this in one pass?
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* first = dummy;
        ListNode* second = dummy;

        // Move first n+1 steps ahead
        for (int i = 0; i <= n; ++i) {
            first = first->next;
        }

        // Move both pointers until first reaches the end
        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }

        // Remove the nth node from the end
        ListNode* nodeToDelete = second->next;
        second->next = second->next->next;
        delete nodeToDelete;

        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;         
    }
};
