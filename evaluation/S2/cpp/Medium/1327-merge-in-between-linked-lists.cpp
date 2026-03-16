// Source: https://leetcode.com/problems/merge-in-between-linked-lists/   |   Difficulty: Medium
//
// Problem Description:
// You are given two linked lists: list1 and list2 of sizes n and m respectively.
//
// Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
//
// The blue edges and nodes in the following figure indicate the result:
//
// Build the result list and return its head.
//
// Example:
// Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
// Output: [10,1,13,1000000,1000001,1000002,5]
// Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place. The blue edges and nodes in the above figure indicate the result.
//
// Constraints:
// 3 <= list1.length <= 104
// 	1 <= a <= b < list1.length - 1
// 	1 <= list2.length <= 104
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* prevA = nullptr;
        ListNode* nodeB = nullptr;
        ListNode* curr = list1;

        for (int i = 0; curr != nullptr; ++i) {
            if (i == a - 1) {
                prevA = curr;
            }
            if (i == b + 1) {
                nodeB = curr;
                break;
            }
            curr = curr->next;
        }

        prevA->next = list2;

        ListNode* tailList2 = list2;
        while (tailList2->next != nullptr) {
            tailList2 = tailList2->next;
        }
        tailList2->next = nodeB;

        return list1;           
    }
};
