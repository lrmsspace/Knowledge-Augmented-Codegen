// Source: https://leetcode.com/problems/palindrome-linked-list/   |   Difficulty: Easy
//
// Problem Description:
// Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
//
// Example:
// Input: head = [1,2,2,1]
// Output: true
//
// Constraints:
// The number of nodes in the list is in the range [1, 105].
// 	0 <= Node.val <= 9
//
//
//  
// Follow up: Could you do it in O(n) time and O(1) space?
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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        ListNode *slow = head, *fast = head, *prev = nullptr;

        // Find the middle of the linked list and reverse the first half
        while (fast && fast->next) {
            fast = fast->next->next;

            ListNode *next = slow->next;
            slow->next = prev;
            prev = slow;
            slow = next;
        }

        // If the length is odd, skip the middle element
        if (fast) {
            slow = slow->next;
        }

        // Compare the reversed first half with the second half
        while (prev && slow) {
            if (prev->val != slow->val) {
                return false;
            }
            prev = prev->next;
            slow = slow->next;
        }

        return true;            
    }
};
