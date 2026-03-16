// Source: https://leetcode.com/problems/remove-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list.
//
// Remove every node which has a node with a greater value anywhere to the right side of it.
//
// Return the head of the modified linked list.
//
// Example:
// Input: head = [5,2,13,3,8]
// Output: [13,8]
// Explanation: The nodes that should be removed are 5, 2 and 3.
// - Node 13 is to the right of node 5.
// - Node 13 is to the right of node 2.
// - Node 8 is to the right of node 3.
//
// Constraints:
// The number of the nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
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
    ListNode* removeNodes(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        stack<ListNode*> stk;

        // Traverse the linked list
        while (curr != nullptr) {
            // Pop nodes from the stack that are less than the current node's value
            while (!stk.empty() && stk.top()->val < curr->val) {
                stk.pop();
            }

            // Link the previous node to the current node if the stack is not empty
            if (!stk.empty()) {
                stk.top()->next = curr;
            } else {
                // If the stack is empty, it means current node is the new head
                head = curr;
            }

            // Push the current node onto the stack
            stk.push(curr);
            prev = curr;
            curr = curr->next;
        }

        // Ensure the last node points to nullptr
        if (prev != nullptr) {
            prev->next = nullptr;
        }

        return head;            
    }
};
