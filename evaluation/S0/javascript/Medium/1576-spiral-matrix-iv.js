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
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {number} m
 * @param {number} n
 * @param {ListNode} head
 * @return {number[][]}
 */
var spiralMatrix = function(m, n, head) {
    const matrix = Array.from({ length: m }, () => new Array(n).fill(-1));
    let top = 0, bottom = m - 1, left = 0, right = n - 1;
    let current = head;

    while (top <= bottom && left <= right && current !== null) {
        for (let col = left; col <= right && current !== null; col++) {
            matrix[top][col] = current.val;
            current = current.next;
        }
        top++;

        for (let row = top; row <= bottom && current !== null; row++) {
            matrix[row][right] = current.val;
            current = current.next;
        }
        right--;

        for (let col = right; col >= left && current !== null; col--) {
            matrix[bottom][col] = current.val;
            current = current.next;
        }
        bottom--;

        for (let row = bottom; row >= top && current !== null; row--) {
            matrix[row][left] = current.val;
            current = current.next;
        }
        left++;
    }

    return matrix;
};