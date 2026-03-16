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
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2){
    struct ListNode* ptr1 = list1;
    struct ListNode* ptr2 = list2;
    struct ListNode* prevA = NULL;
    struct ListNode* afterB = NULL;
    int index = 0;

    // Find the (a-1)th node and the (b+1)th node in list1
    while (ptr1 != NULL) {
        if (index == a - 1) {
            prevA = ptr1;
        }
        if (index == b + 1) {
            afterB = ptr1;
            break;
        }
        ptr1 = ptr1->next;
        index++;
    }

    // Connect (a-1)th node to the head of list2
    if (prevA != NULL) {
        prevA->next = list2;
    }

    // Traverse to the end of list2
    while (ptr2->next != NULL) {
        ptr2 = ptr2->next;
    }

    // Connect the end of list2 to the (b+1)th node
    ptr2->next = afterB;

    return list1;
}
