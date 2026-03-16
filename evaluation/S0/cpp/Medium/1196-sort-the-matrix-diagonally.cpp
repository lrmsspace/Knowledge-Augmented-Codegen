// Source: https://leetcode.com/problems/sort-the-matrix-diagonally/   |   Difficulty: Medium
//
// Problem Description:
// A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until reaching the matrix's end. For example, the matrix diagonal starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0], mat[3][1], and mat[4][2].
//
// Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order and return the resulting matrix.
//
// Example:
// Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
// Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 100
// 	1 <= mat[i][j] <= 100
//

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        // Sort diagonals starting from the first column
        for (int row = 0; row < m; ++row) {
            sortDiagonal(mat, row, 0, m, n);
        }

        // Sort diagonals starting from the first row (excluding the top-left corner)
        for (int col = 1; col < n; ++col) {
            sortDiagonal(mat, 0, col, m, n);
        }

        return mat;         
    }
};
