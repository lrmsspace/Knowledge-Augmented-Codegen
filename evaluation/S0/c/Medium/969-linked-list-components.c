// Source: https://leetcode.com/problems/linked-list-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list containing unique integer values and an integer array nums that is a subset of the linked list values.
//
// Return the number of connected components in nums where two values are connected if they appear consecutively in the linked list.
//
// Example:
// Input: head = [0,1,2,3], nums = [0,1,3]
// Output: 2
// Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.
//
// Constraints:
// The number of nodes in the linked list is n.
// 	1 <= n <= 104
// 	0 <= Node.val < n
// 	All the values Node.val are unique.
// 	1 <= nums.length <= n
// 	0 <= nums[i] < n
// 	All the values of nums are unique.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int numComponents(struct ListNode* head, int* nums, int numsSize) {
    int count = 0;
    int inComponent = 0;
    int numSet[10000] = {0}; // Assuming the maximum value of Node.val is less than 10000

    // Populate the set for quick lookup
    for (int i = 0; i < numsSize; i++) {
        numSet[nums[i]] = 1;
    }

    struct ListNode* current = head;
    while (current != NULL) {
        if (numSet[current->val]) {
            if (!inComponent) {
                count++;
                inComponent = 1;
            }
        } else {
            inComponent = 0;
        }
        current = current->next;
    }

    return count;       
}
