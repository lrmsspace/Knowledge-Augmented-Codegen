// Source: https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.
//
// Example:
// Input: nums = [1,2,3], head = [1,2,3,4,5]
//
// Output: [4,5]
//
// Explanation:
//
//
//
// Remove the nodes with values 1, 2, and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	All elements in nums are unique.
// 	The number of nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	The input is generated such that there is at least one node in the linked list that has a value not present in nums.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {
    // Create a hash set to store the values in nums for O(1) lookup
    int maxVal = 100000; // Given constraint: 1 <= Node.val <= 10^5
    bool* hashSet = (bool*)calloc(maxVal + 1, sizeof(bool));
    for (int i = 0; i < numsSize; i++) {
        hashSet[nums[i]] = true;
    }

    // Create a dummy node to simplify edge cases
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    struct ListNode* current = dummy;

    // Traverse the linked list and remove nodes present in the hash set
    while (current->next != NULL) {
        if (hashSet[current->next->val]) {
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp); // Free the removed node
        } else {
            current = current->next;
        }
    }

    struct ListNode* modifiedHead = dummy->next;
    free(dummy); // Free the dummy node
    free(hashSet); // Free the hash set
    return modifiedHead;        
}
