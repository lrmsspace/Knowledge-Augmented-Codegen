// Source: https://leetcode.com/problems/lucky-numbers-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
//
// A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
//
// Example:
// Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
// Output: [15]
// Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= n, m <= 50
// 	1 <= matrix[i][j] <= 105.
// 	All elements in the matrix are distinct.
//

class Solution {
public:
    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> rowMin(m, INT_MAX);
        vector<int> colMax(n, INT_MIN);
        vector<int> luckyNumbers;

        // Find the minimum in each row
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowMin[i] = min(rowMin[i], matrix[i][j]);
            }
        }

        // Find the maximum in each column
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                colMax[j] = max(colMax[j], matrix[i][j]);
            }
        }

        // Identify lucky numbers
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == rowMin[i] && matrix[i][j] == colMax[j]) {
                    luckyNumbers.push_back(matrix[i][j]);
                }
            }
        }

        return luckyNumbers;            
    }
};
