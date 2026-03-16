// Source: https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// There is an m x n matrix that is initialized to all 0's. There is also a 2D array indices where each indices[i] = [ri, ci] represents a 0-indexed location to perform some increment operations on the matrix.
//
// For each location indices[i], do both of the following:
//
//
// 	Increment all the cells on row ri.
// 	Increment all the cells on column ci.
//
//
// Given m, n, and indices, return the number of odd-valued cells in the matrix after applying the increment to all locations in indices.
//
// Example:
// Input: m = 2, n = 3, indices = [[0,1],[1,1]]
// Output: 6
// Explanation: Initial matrix = [[0,0,0],[0,0,0]].
// After applying first increment it becomes [[1,2,1],[0,1,0]].
// The final matrix is [[1,3,1],[1,3,1]], which contains 6 odd numbers.
//
// Constraints:
// 1 <= m, n <= 50
// 	1 <= indices.length <= 100
// 	0 <= ri < m
// 	0 <= ci < n
//
//
//  
// Follow up: Could you solve this in O(n + m + indices.length) time with only O(n + m) extra space?
//

int oddCells(int m, int n, int** indices, int indicesSize, int* indicesColSize) {
    int row[50] = {0};
    int col[50] = {0};
    for (int i = 0; i < indicesSize; i++) {
        row[indices[i][0]] ^= 1;
        col[indices[i][1]] ^= 1;
    }
    int oddRowCount = 0;
    for (int i = 0; i < m; i++) {
        if (row[i]) {
            oddRowCount++;
        }
    }
    int oddColCount = 0;
    for (int j = 0; j < n; j++) {
        if (col[j]) {
            oddColCount++;
        }
    }
    return oddRowCount * n + oddColCount * m - 2 * oddRowCount * oddColCount;       
}
