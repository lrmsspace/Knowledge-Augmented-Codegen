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
    public int[][] spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int total = rows * cols;
        int[][] result = new int[total][2];
        int count = 0;
        result[count++] = new int[]{rStart, cStart};

        int step = 1;
        int[][] directions = new int[][]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right, down, left, up
        int dirIndex = 0;

        while (count < total) {
            for (int i = 0; i < 2; i++) { // two sides for each step size
                for (int j = 0; j < step; j++) {
                    rStart += directions[dirIndex][0];
                    cStart += directions[dirIndex][1];

                    if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {
                        result[count++] = new int[]{rStart, cStart};
                    }
                }
                dirIndex = (dirIndex + 1) % 4; // change direction
            }
            step++; // increase step size after completing two sides
        }

        return result;          
    }
}
