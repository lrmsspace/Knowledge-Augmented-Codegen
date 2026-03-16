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
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* first = head;
        ListNode* second = head;
        ListNode* current = head;
        int count = 1;

        // Find the kth node from the beginning
        while (count < k) {
            first = first->next;
            count++;
        }

        ListNode* kthFromStart = first;

        // Continue to the end to find the kth node from the end
        while (current->next != nullptr) {
            current = current->next;
            if (count >= k) {
                second = second->next;
            }
            count++;
        }

        // Swap values of the two nodes
        int temp = kthFromStart->val;
        kthFromStart->val = second->val;
        second->val = temp;

        return head;            
    }
};
