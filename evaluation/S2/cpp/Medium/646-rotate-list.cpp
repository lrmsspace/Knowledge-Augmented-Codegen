// Source: https://leetcode.com/problems/rotate-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list, rotate the list to the right by k places.
//
// Example:
// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
//
// Constraints:
// The number of nodes in the list is in the range [0, 500].
// 	-100 <= Node.val <= 100
// 	0 <= k <= 2 * 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || k == 0) return head;

        // Find the length of the list and the tail node
        ListNode* tail = head;
        int length = 1; // Start with 1 since we're already at head
        while (tail->next) {
            tail = tail->next;
            length++;
        }

        // Connect the tail to the head to make it circular
        tail->next = head;

        // Calculate the effective rotations needed
        k = k % length;
        int stepsToNewHead = length - k;

        // Find the new tail and new head
        ListNode* newTail = tail;
        while (stepsToNewHead--) {
            newTail = newTail->next;
        }
        ListNode* newHead = newTail->next;

        // Break the circle
        newTail->next = nullptr;

        return newHead;         
    }
};
