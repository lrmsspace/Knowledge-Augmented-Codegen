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
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeZeroSumSublists(struct ListNode* head) {
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = head;

    // First pass: Compute the prefix sums and store the last occurrence of each sum
    struct ListNode* curr = &dummy;
    int prefixSum = 0;
    // Using a hash map to store prefix sums and their corresponding nodes
    #define HASH_SIZE 2003
    struct ListNode* hash[HASH_SIZE] = {0};

    while (curr) {
        prefixSum += curr->val;
        int hashIndex = (prefixSum % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
        hash[hashIndex] = curr; // Store the last occurrence of this prefix sum
        curr = curr->next;
    }

    // Second pass: Remove zero-sum subsequences
    curr = &dummy;
    prefixSum = 0;

    while (curr) {
        prefixSum += curr->val;
        int hashIndex = (prefixSum % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
        struct ListNode* lastOccurrence = hash[hashIndex];
        if (lastOccurrence != curr) {
            // Bypass the nodes between curr and lastOccurrence
            curr->next = lastOccurrence->next;
        }
        curr = curr->next;
    }

    return dummy.next;      
}
