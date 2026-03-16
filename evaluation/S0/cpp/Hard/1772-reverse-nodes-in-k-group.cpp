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
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prevGroupEnd = dummy;
        
        while (true) {
            // Check if there are k nodes left
            ListNode* kthNode = prevGroupEnd;
            for (int i = 0; i < k; i++) {
                kthNode = kthNode->next;
                if (!kthNode) {
                    // Less than k nodes left, return result
                    ListNode* result = dummy->next;
                    delete dummy;
                    return result;
                }
            }
            
            // Reverse k nodes
            ListNode* groupStart = prevGroupEnd->next;
            ListNode* nextGroupStart = kthNode->next;
            ListNode* prev = nextGroupStart;
            ListNode* curr = groupStart;
            
            for (int i = 0; i < k; i++) {
                ListNode* temp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = temp;
            }
            
            // Connect previous group to reversed group
            prevGroupEnd->next = kthNode;
            prevGroupEnd = groupStart;
        }
        
        return dummy->next;  // This line will never be reached         
    }
};
