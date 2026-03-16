// Source: https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/   |   Difficulty: Medium
//
// Problem Description:
// A critical point in a linked list is defined as either a local maxima or a local minima.
//
// A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.
//
// A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.
//
// Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.
//
// Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points. If there are fewer than two critical points, return [-1, -1].
//
// Example:
// Input: head = [3,1]
// Output: [-1,-1]
// Explanation: There are no critical points in [3,1].
//
// Constraints:
// The number of nodes in the list is in the range [2, 105].
// 	1 <= Node.val <= 105
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
int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = -1;
    result[1] = -1;
    *returnSize = 2;

    if (!head || !head->next || !head->next->next) {
        return result;
    }

    int first_cp_index = -1;
    int prev_cp_index = -1;
    int min_distance = INT_MAX;
    int max_distance = -1;
    int index = 1;

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;
    struct ListNode* next = curr->next;

    while (next) {
        if ((curr->val > prev->val && curr->val > next->val) ||
            (curr->val < prev->val && curr->val < next->val)) {
            if (first_cp_index == -1) {
                first_cp_index = index;
            } else {
                min_distance = fmin(min_distance, index - prev_cp_index);
                max_distance = index - first_cp_index;
            }
            prev_cp_index = index;
        }
        prev = curr;
        curr = next;
        next = next->next;
        index++;
    }

    if (max_distance == -1) {
        return result;
    }

    result[0] = min_distance;
    result[1] = max_distance;
    return result;      
}
