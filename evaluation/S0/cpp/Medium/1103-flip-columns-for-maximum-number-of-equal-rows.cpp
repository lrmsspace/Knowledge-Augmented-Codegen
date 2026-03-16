// Source: https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix matrix.
//
// You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).
//
// Return the maximum number of rows that have all values equal after some number of flips.
//
// Example:
// Input: matrix = [[0,1],[1,1]]
// Output: 1
// Explanation: After flipping no values, 1 row has all values equal.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 300
// 	matrix[i][j] is either 0 or 1.
//

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<string, int> patternCount;
        int maxRows = 0;

        for (const auto& row : matrix) {
            string pattern;
            for (int val : row) {
                pattern += (val == row[0]) ? '0' : '1';
            }
            patternCount[pattern]++;
            maxRows = max(maxRows, patternCount[pattern]);
        }

        return maxRows;         
    }
};
