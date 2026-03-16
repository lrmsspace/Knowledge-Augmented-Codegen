// Source: https://leetcode.com/problems/split-linked-list-in-parts/   |   Difficulty: Medium
//
// Problem Description:
// Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
//
// The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.
//
// The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.
//
// Return an array of the k parts.
//
// Example:
// Input: head = [1,2,3], k = 5
// Output: [[1],[2],[3],[],[]]
// Explanation:
// The first element output[0] has output[0].val = 1, output[0].next = null.
// The last element output[4] is null, but its string representation as a ListNode is [].
//
// Constraints:
// The number of nodes in the list is in the range [0, 1000].
// 	0 <= Node.val <= 1000
// 	1 <= k <= 50
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct ListNode** splitListToParts(struct ListNode* head, int k, int* returnSize) {
    struct ListNode** parts = (struct ListNode**)malloc(k * sizeof(struct ListNode*));
    int total_nodes = 0;
    struct ListNode* current = head;

    // Count total nodes in the linked list
    while (current) {
        total_nodes++;
        current = current->next;
    }

    int base_size = total_nodes / k; // Minimum size of each part
    int extra_nodes = total_nodes % k; // Extra nodes to distribute

    current = head;
    for (int i = 0; i < k; i++) {
        parts[i] = current;
        int current_part_size = base_size + (i < extra_nodes ? 1 : 0);

        // Traverse to the end of the current part
        for (int j = 0; j < current_part_size - 1; j++) {
            if (current) {
                current = current->next;
            }
        }

        // If there are nodes in the current part, disconnect it from the rest
        if (current) {
            struct ListNode* next_part_head = current->next;
            current->next = NULL;
            current = next_part_head;
        }
    }

    *returnSize = k;
    return parts;       
}
