// Source: https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a linked list head, in which each node contains an integer value.
//
// Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.
//
// Return the linked list after insertion.
//
// The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
//
// Example:
// Input: head = [18,6,10,3]
// Output: [18,6,6,2,10,1,3]
// Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
// - We insert the greatest common divisor of 18 and 6 = 6 between the 1st and the 2nd nodes.
// - We insert the greatest common divisor of 6 and 10 = 2 between the 2nd and the 3rd nodes.
// - We insert the greatest common divisor of 10 and 3 = 1 between the 3rd and the 4th nodes.
// There are no more adjacent nodes, so we return the linked list.
//
// Constraints:
// The number of nodes in the list is in the range [1, 5000].
// 	1 <= Node.val <= 1000
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertGreatestCommonDivisors(struct ListNode* head) {
    struct ListNode* curr = head;
    while (curr && curr->next) {
        int a = curr->val;
        int b = curr->next->val;

        // Compute GCD using Euclidean algorithm
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        int gcd = a;

        // Create new node with GCD value
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = gcd;

        // Insert new node between curr and curr->next
        newNode->next = curr->next;
        curr->next = newNode;

        // Move to the next original node
        curr = newNode->next;
    }
    return head;        
}
