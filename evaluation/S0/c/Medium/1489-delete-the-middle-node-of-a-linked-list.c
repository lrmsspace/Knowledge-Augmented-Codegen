// Source: https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list. Delete the middle node, and return the head of the modified linked list.
//
// The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.
//
//
// 	For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.
//
// Example:
// Input: head = [1,3,4,7,1,2,6]
// Output: [1,3,4,1,2,6]
// Explanation:
// The above figure represents the given linked list. The indices of the nodes are written below.
// Since n = 7, node 3 with value 7 is the middle node, which is marked in red.
// We return the new list after removing this node.
//
// Constraints:
// The number of nodes in the list is in the range [1, 105].
// 	1 <= Node.val <= 105
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteMiddle(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    struct ListNode* slow = head;
    struct ListNode* fast = head;
    struct ListNode* prev = NULL;

    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // 'slow' is now pointing to the middle node
    // 'prev' is the node before the middle node
    if (prev != NULL) {
        prev->next = slow->next;
    }

    // Free the memory of the deleted middle node if necessary
    // free(slow); // Uncomment if dynamic memory allocation was used

    return head;        
}
