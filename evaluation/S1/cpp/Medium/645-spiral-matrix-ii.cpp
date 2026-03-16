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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int left = 0, right = n - 1;
        int top = 0, bottom = n - 1;
        int num = 1;

        while (left <= right && top <= bottom) {
            // Fill top row
            for (int j = left; j <= right; ++j) {
                matrix[top][j] = num++;
            }
            top++;

            // Fill right column
            for (int i = top; i <= bottom; ++i) {
                matrix[i][right] = num++;
            }
            right--;

            if (top <= bottom) {
                // Fill bottom row
                for (int j = right; j >= left; --j) {
                    matrix[bottom][j] = num++;
                }
                bottom--;
            }

            if (left <= right) {
                // Fill left column
                for (int i = bottom; i >= top; --i) {
                    matrix[i][left] = num++;
                }
                left++;
            }
        }

        return matrix;          
    }
};
