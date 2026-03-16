// Source: https://leetcode.com/problems/search-a-2d-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix matrix with the following two properties:
//
//
// 	Each row is sorted in non-decreasing order.
// 	The first integer of each row is greater than the last integer of the previous row.
//
//
// Given an integer target, return true if target is in matrix or false otherwise.
//
// You must write a solution in O(log(m * n)) time complexity.
//
// Example:
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 100
// 	-104 <= matrix[i][j], target <= 104
//

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int left = 0, right = rows * cols - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int mid_value = matrix[mid / cols][mid % cols];

        if (mid_value == target) {
            return true;
        } else if (mid_value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;       
}
