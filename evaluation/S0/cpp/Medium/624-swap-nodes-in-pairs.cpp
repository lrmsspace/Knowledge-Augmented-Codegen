// Source: https://leetcode.com/problems/swap-nodes-in-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
//
// Example:
// Input: head = [1,2,3,4]
//
// Output: [2,1,4,3]
//
// Explanation:
//
// Constraints:
// The number of nodes in the list is in the range [0, 100].
// 	0 <= Node.val <= 100
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
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        while (prev->next && prev->next->next) {
            ListNode* first = prev->next;
            ListNode* second = first->next;

            // Swapping
            first->next = second->next;
            second->next = first;
            prev->next = second;

            // Move prev to the next pair
            prev = first;
        }

        return dummy.next;          
    }
};
