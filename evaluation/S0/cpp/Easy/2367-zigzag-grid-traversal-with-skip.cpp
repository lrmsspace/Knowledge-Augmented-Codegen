// Source: https://leetcode.com/problems/zigzag-grid-traversal-with-skip/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n 2D array grid of positive integers.
//
// Your task is to traverse grid in a zigzag pattern while skipping every alternate cell.
//
// Zigzag pattern traversal is defined as following the below actions:
//
//
// 	Start at the top-left cell (0, 0).
// 	Move right within a row until the end of the row is reached.
// 	Drop down to the next row, then traverse left until the beginning of the row is reached.
// 	Continue alternating between right and left traversal until every row has been traversed.
//
//
// Note that you must skip every alternate cell during the traversal.
//
// Return an array of integers result containing, in order, the value of the cells visited during the zigzag traversal with skips.
//
// Example:
// Input: grid = [[1,2],[3,4]]
//
// Output: [1,4]
//
// Explanation:
//
// Constraints:
// 2 <= n == grid.length <= 50
// 	2 <= m == grid[i].length <= 50
// 	1 <= grid[i][j] <= 2500
//

class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        vector<int> result;
        int rows = grid.size();
        int cols = grid[0].size();
        bool leftToRight = true;

        for (int r = 0; r < rows; ++r) {
            if (leftToRight) {
                for (int c = 0; c < cols; c += 2) {
                    result.push_back(grid[r][c]);
                }
            } else {
                for (int c = cols - 1; c >= 0; c -= 2) {
                    result.push_back(grid[r][c]);
                }
            }
            leftToRight = !leftToRight;
        }

        return result;          
    }
};
