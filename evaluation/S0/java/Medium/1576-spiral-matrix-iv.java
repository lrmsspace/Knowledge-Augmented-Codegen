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
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public int[][] spiralMatrix(int m, int n, ListNode head) {
        int[][] matrix = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = -1;
            }
        }

        int top = 0, bottom = m - 1, left = 0, right = n - 1;
        ListNode current = head;

        while (top <= bottom && left <= right && current != null) {
            for (int col = left; col <= right && current != null; col++) {
                matrix[top][col] = current.val;
                current = current.next;
            }
            top++;

            for (int row = top; row <= bottom && current != null; row++) {
                matrix[row][right] = current.val;
                current = current.next;
            }
            right--;

            for (int col = right; col >= left && current != null; col--) {
                matrix[bottom][col] = current.val;
                current = current.next;
            }
            bottom--;

            for (int row = bottom; row >= top && current != null; row--) {
                matrix[row][left] = current.val;
                current = current.next;
            }
            left++;
        }

        return matrix;          
    }
}
