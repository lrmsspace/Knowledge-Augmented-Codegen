// Source: https://leetcode.com/problems/partition-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//
// You should preserve the original relative order of the nodes in each of the two partitions.
//
// Example:
// Input: head = [1,4,3,2,5,2], x = 3
// Output: [1,2,2,4,3,5]
//
// Constraints:
// The number of nodes in the list is in the range [0, 200].
// 	-100 <= Node.val <= 100
// 	-200 <= x <= 200
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
    ListNode* partition(ListNode* head, int x) {
        if (!head) return nullptr;

        ListNode* lessHead = new ListNode(0); // Dummy head for less than x
        ListNode* greaterHead = new ListNode(0); // Dummy head for greater than or equal to x

        ListNode* less = lessHead; // Pointer to build the less than x list
        ListNode* greater = greaterHead; // Pointer to build the greater than or equal to x list

        while (head) {
            if (head->val < x) {
                less->next = head; // Add to less list
                less = less->next;
            } else {
                greater->next = head; // Add to greater list
                greater = greater->next;
            }
            head = head->next; // Move to the next node
        }

        greater->next = nullptr; // Terminate the greater list
        less->next = greaterHead->next; // Connect the two lists

        ListNode* partitionedHead = lessHead->next; // The head of the partitioned list

        delete lessHead; // Clean up dummy nodes
        delete greaterHead;

        return partitionedHead;         
    }
};
