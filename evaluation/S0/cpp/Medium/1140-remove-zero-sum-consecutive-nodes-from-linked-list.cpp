// Source: https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
//
// After doing so, return the head of the final linked list.  You may return any such answer.
//
//  
// (Note that in the examples below, all sequences are serializations of ListNode objects.)
//
// Example:
// Input: head = [1,2,-3,3,1]
// Output: [3,1]
// Note: The answer [1,2,1] would also be accepted.
//
// Constraints:
// The given linked list will contain between 1 and 1000 nodes.
// 	Each node in the linked list has -1000 <= node.val <= 1000.
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        unordered_map<int, ListNode*> prefixSumMap;
        int prefixSum = 0;
        ListNode* current = &dummy;

        // First pass: build the prefix sum map
        while (current) {
            prefixSum += current->val;
            prefixSumMap[prefixSum] = current;
            current = current->next;
        }

        // Second pass: remove zero-sum sequences
        prefixSum = 0;
        current = &dummy;
        while (current) {
            prefixSum += current->val;
            current->next = prefixSumMap[prefixSum]->next;
            current = current->next;
        }

        return dummy.next;          
    }
};
