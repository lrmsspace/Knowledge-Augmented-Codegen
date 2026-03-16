// Source: https://leetcode.com/problems/merge-nodes-in-between-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have Node.val == 0.
//
// For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes. The modified list should not contain any 0's.
//
// Return the head of the modified linked list.
//
// Example:
// Input: head = [0,3,1,0,4,5,2,0]
// Output: [4,11]
// Explanation: 
// The above figure represents the given linked list. The modified list contains
// - The sum of the nodes marked in green: 3 + 1 = 4.
// - The sum of the nodes marked in red: 4 + 5 + 2 = 11.
//
// Constraints:
// The number of nodes in the list is in the range [3, 2 * 105].
// 	0 <= Node.val <= 1000
// 	There are no two consecutive nodes with Node.val == 0.
// 	The beginning and end of the linked list have Node.val == 0.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeNodes(struct ListNode* head) {
    struct ListNode* curr = head->next;
    struct ListNode* newHead = NULL;
    struct ListNode* newTail = NULL;
    
    while (curr != NULL) {
        int sum = 0;
        
        // Sum values until the next zero
        while (curr != NULL && curr->val != 0) {
            sum += curr->val;
            curr = curr->next;
        }
        
        // Create a new node with the sum if it's not zero
        if (sum > 0) {
            struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
            newNode->val = sum;
            newNode->next = NULL;
            
            if (newHead == NULL) {
                newHead = newNode;
                newTail = newNode;
            } else {
                newTail->next = newNode;
                newTail = newNode;
            }
        }
        
        // Move to the next node after zero
        if (curr != NULL) {
            curr = curr->next;
        }
    }
    
    return newHead;     
}
