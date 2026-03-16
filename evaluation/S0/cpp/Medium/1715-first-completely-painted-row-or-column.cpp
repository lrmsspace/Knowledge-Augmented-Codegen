// Source: https://leetcode.com/problems/first-completely-painted-row-or-column/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].
//
// Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].
//
// Return the smallest index i at which either a row or a column will be completely painted in mat.
//
// Example:
// Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
// Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
//
// Constraints:
// m == mat.length
// 	n = mat[i].length
// 	arr.length == m * n
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= arr[i], mat[r][c] <= m * n
// 	All the integers of arr are unique.
// 	All the integers of mat are unique.
//

class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);
        unordered_map<int, pair<int, int>> valueToPosition;

        // Map each value in mat to its (row, column) position
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                valueToPosition[mat[i][j]] = {i, j};
            }
        }

        // Process each value in arr
        for (int i = 0; i < arr.size(); ++i) {
            auto [row, col] = valueToPosition[arr[i]];
            rowCount[row]++;
            colCount[col]++;

            // Check if the current row or column is completely painted
            if (rowCount[row] == n || colCount[col] == m) {
                return i;
            }
        }

        return -1; // This line should never be reached given the problem constraints           
    }
};
