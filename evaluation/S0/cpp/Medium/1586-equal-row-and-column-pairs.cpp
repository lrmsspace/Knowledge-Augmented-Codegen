// Source: https://leetcode.com/problems/equal-row-and-column-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.
//
// A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).
//
// Example:
// Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
// Output: 1
// Explanation: There is 1 equal row and column pair:
// - (Row 2, Column 1): [2,7,7]
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 200
// 	1 <= grid[i][j] <= 105
//

class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        unordered_map<string, int> rowCount;

        // Count the frequency of each row represented as a string
        for (const auto& row : grid) {
            string rowKey;
            for (int val : row) {
                rowKey += to_string(val) + ",";
            }
            rowCount[rowKey]++;
        }

        int result = 0;

        // For each column, create its string representation and check against rowCount
        for (int col = 0; col < n; ++col) {
            string colKey;
            for (int row = 0; row < n; ++row) {
                colKey += to_string(grid[row][col]) + ",";
            }
            if (rowCount.find(colKey) != rowCount.end()) {
                result += rowCount[colKey];
            }
        }

        return result;          
    }
};
