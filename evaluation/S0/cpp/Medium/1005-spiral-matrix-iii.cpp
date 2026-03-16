// Source: https://leetcode.com/problems/spiral-matrix-iii/   |   Difficulty: Medium
//
// Problem Description:
// You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
//
// You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
//
// Return an array of coordinates representing the positions of the grid in the order you visited them.
//
// Example:
// Input: rows = 1, cols = 4, rStart = 0, cStart = 0
// Output: [[0,0],[0,1],[0,2],[0,3]]
//
// Constraints:
// 1 <= rows, cols <= 100
// 	0 <= rStart < rows
// 	0 <= cStart < cols
//

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> result;
        result.reserve(rows * cols);

        // Directions: East, South, West, North
        vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        int dirIndex = 0; // Start facing East
        int stepSize = 1; // Initial step size
        int r = rStart;
        int c = cStart;

        result.push_back({r, c});

        while (result.size() < rows * cols) {
            for (int i = 0; i < 2; ++i) { // Two directions for each step size
                for (int step = 0; step < stepSize; ++step) {
                    r += directions[dirIndex].first;
                    c += directions[dirIndex].second;

                    if (r >= 0 && r < rows && c >= 0 && c < cols) {
                        result.push_back({r, c});
                        if (result.size() == rows * cols) {
                            return result;
                        }
                    }
                }
                dirIndex = (dirIndex + 1) % 4; // Turn clockwise
            }
            stepSize++; // Increase step size after two directions
        }

        return result;          
    }
};
