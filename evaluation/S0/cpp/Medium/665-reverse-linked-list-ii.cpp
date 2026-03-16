// Source: https://leetcode.com/problems/reverse-linked-list-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.
//
// Example:
// Input: head = [1,2,3,4,5], left = 2, right = 4
// Output: [1,4,3,2,5]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= n <= 500
// 	-500 <= Node.val <= 500
// 	1 <= left <= right <= n
//
//
//  
// Follow up: Could you do it in one pass?
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || left == right) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        // Move `prev` to the node before the `left` position
        for (int i = 1; i < left; ++i) {
            prev = prev->next;
        }

        ListNode* const reverse_start = prev->next;
        ListNode* curr = reverse_start->next;

        // Reverse the sublist from left to right
        for (int i = 0; i < right - left; ++i) {
            reverse_start->next = curr->next;
            curr->next = prev->next;
            prev->next = curr;
            curr = reverse_start->next;
        }

        return dummy.next;          
    }
};
