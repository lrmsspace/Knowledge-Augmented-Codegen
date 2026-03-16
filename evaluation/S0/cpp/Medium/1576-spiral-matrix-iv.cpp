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
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> matrix(m, vector<int>(n, -1));
        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;
        ListNode* current = head;

        while (top <= bottom && left <= right && current != nullptr) {
            // Traverse from left to right
            for (int col = left; col <= right && current != nullptr; ++col) {
                matrix[top][col] = current->val;
                current = current->next;
            }
            top++;

            // Traverse from top to bottom
            for (int row = top; row <= bottom && current != nullptr; ++row) {
                matrix[row][right] = current->val;
                current = current->next;
            }
            right--;

            // Traverse from right to left
            for (int col = right; col >= left && current != nullptr; --col) {
                matrix[bottom][col] = current->val;
                current = current->next;
            }
            bottom--;

            // Traverse from bottom to top
            for (int row = bottom; row >= top && current != nullptr; --row) {
                matrix[row][left] = current->val;
                current = current->next;
            }
            left++;
        }

        return matrix;          
    }
};
