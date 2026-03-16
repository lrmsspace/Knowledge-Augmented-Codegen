// Source: https://leetcode.com/problems/spiral-matrix-iv/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n, which represent the dimensions of a matrix.
//
// You are also given the head of a linked list of integers.
//
// Generate an m x n matrix that contains the integers in the linked list presented in spiral order (clockwise), starting from the top-left of the matrix. If there are remaining empty spaces, fill them with -1.
//
// Return the generated matrix.
//
// Example:
// Input: m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
// Output: [[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
// Explanation: The diagram above shows how the values are printed in the matrix.
// Note that the remaining spaces in the matrix are filled with -1.
//
// Constraints:
// 1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	The number of nodes in the list is in the range [1, m * n].
// 	0 <= Node.val <= 1000
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** spiralMatrix(int m, int n, struct ListNode* head, int* returnSize, int** returnColumnSizes) {
    int** matrix = (int**)malloc(m * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = -1; // Initialize with -1
        }
    }

    int top = 0, bottom = m - 1, left = 0, right = n - 1;
    struct ListNode* current = head;

    while (top <= bottom && left <= right && current != NULL) {
        // Traverse from left to right
        for (int j = left; j <= right && current != NULL; j++) {
            matrix[top][j] = current->val;
            current = current->next;
        }
        top++;

        // Traverse from top to bottom
        for (int i = top; i <= bottom && current != NULL; i++) {
            matrix[i][right] = current->val;
            current = current->next;
        }
        right--;

        // Traverse from right to left
        for (int j = right; j >= left && current != NULL; j--) {
            matrix[bottom][j] = current->val;
            current = current->next;
        }
        bottom--;

        // Traverse from bottom to top
        for (int i = bottom; i >= top && current != NULL; i--) {
            matrix[i][left] = current->val;
            current = current->next;
        }
        left++;
    }

    *returnSize = m;
    return matrix;      
}
