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
        ListNode* curr = list1;
        int index = 0;

        // Find the (a-1)th node
        while (index < a) {
            prevA = curr;
            curr = curr->next;
            index++;
        }

        // Now curr is at ath node, we need to move to (b+1)th node
        ListNode* afterB = curr;
        while (index <= b) {
            afterB = afterB->next;
            index++;
        }

        // Connect (a-1)th node to head of list2
        prevA->next = list2;

        // Find the tail of list2
        ListNode* tailList2 = list2;
        while (tailList2->next != nullptr) {
            tailList2 = tailList2->next;
        }

        // Connect tail of list2 to (b+1)th node
        tailList2->next = afterB;

        return list1;           
    }
};
