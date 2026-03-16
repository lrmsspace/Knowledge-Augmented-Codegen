// Source: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
//
// Return the head of the linked list after doubling it.
//
// Example:
// Input: head = [1,8,9]
// Output: [3,7,8]
// Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
//
// Constraints:
// The number of nodes in the list is in the range [1, 104]
// 	0 <= Node.val <= 9
// 	The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.
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
    ListNode* doubleIt(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* curr = head;
        ListNode* lastNotNine = dummy;

        // Find the rightmost node that is not 9
        while (curr) {
            if (curr->val != 9) {
                lastNotNine = curr;
            }
            curr = curr->next;
        }

        // Double the value at lastNotNine
        lastNotNine->val += 1;
        curr = lastNotNine->next;

        // Set all following 9s to 0
        while (curr) {
            curr->val = 0;
            curr = curr->next;
        }

        // If dummy's value is still 0, return head; otherwise return dummy
        return dummy->val == 0 ? head : dummy;          
    }
};
