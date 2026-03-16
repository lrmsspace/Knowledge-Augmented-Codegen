// Source: https://leetcode.com/problems/next-greater-node-in-linked-list/   |   Difficulty: Medium
//
// Problem Description:
// You are given the head of a linked list with n nodes.
//
// For each node in the list, find the value of the next greater node. That is, for each node, find the value of the first node that is next to it and has a strictly larger value than it.
//
// Return an integer array answer where answer[i] is the value of the next greater node of the ith node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.
//
// Example:
// Input: head = [2,1,5]
// Output: [5,5,0]
//
// Constraints:
// The number of nodes in the list is n.
// 	1 <= n <= 104
// 	1 <= Node.val <= 109
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
int* nextLargerNodes(struct ListNode* head, int* returnSize) {
    // First, we need to determine the size of the linked list
    int size = 0;
    struct ListNode* current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    // Allocate memory for the result array
    int* result = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        result[i] = 0; // Initialize all elements to 0
    }

    // Create an array to hold the values of the linked list nodes
    int* values = (int*)malloc(size * sizeof(int));
    current = head;
    for (int i = 0; i < size; i++) {
        values[i] = current->val;
        current = current->next;
    }

    // Use a stack to keep track of indices of nodes
    int* stack = (int*)malloc(size * sizeof(int));
    int top = -1; // Stack is initially empty

    for (int i = 0; i < size; i++) {
        // While stack is not empty and the current value is greater than the value at the index stored at the top of the stack
        while (top >= 0 && values[i] > values[stack[top]]) {
            result[stack[top]] = values[i]; // Update the result for that index
            top--; // Pop from stack
        }
        // Push the current index onto the stack
        stack[++top] = i;
    }

    // Clean up
    free(values);
    free(stack);

    *returnSize = size;
    return result;      
}
