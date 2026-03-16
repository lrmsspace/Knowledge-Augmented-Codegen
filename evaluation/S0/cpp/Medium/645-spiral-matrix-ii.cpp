// Source: https://leetcode.com/problems/spiral-matrix-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
//
// Example:
// Input: n = 3
// Output: [[1,2,3],[8,9,4],[7,6,5]]
//
// Constraints:
// 1 <= n <= 20
//

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int left = 0, right = n - 1, top = 0, bottom = n - 1;
        int num = 1;

        while (left <= right && top <= bottom) {
            // Fill top row
            for (int col = left; col <= right; ++col) {
                matrix[top][col] = num++;
            }
            top++;

            // Fill right column
            for (int row = top; row <= bottom; ++row) {
                matrix[row][right] = num++;
            }
            right--;

            // Fill bottom row
            if (top <= bottom) {
                for (int col = right; col >= left; --col) {
                    matrix[bottom][col] = num++;
                }
                bottom--;
            }

            // Fill left column
            if (left <= right) {
                for (int row = bottom; row >= top; --row) {
                    matrix[row][left] = num++;
                }
                left++;
            }
        }

        return matrix;          
    }
};
