// Source: https://leetcode.com/problems/matrix-cells-in-distance-order/   |   Difficulty: Easy
//
// Problem Description:
// You are given four integers row, cols, rCenter, and cCenter. There is a rows x cols matrix and you are on the cell with the coordinates (rCenter, cCenter).
//
// Return the coordinates of all cells in the matrix, sorted by their distance from (rCenter, cCenter) from the smallest distance to the largest distance. You may return the answer in any order that satisfies this condition.
//
// The distance between two cells (r1, c1) and (r2, c2) is |r1 - r2| + |c1 - c2|.
//
// Example:
// Input: rows = 1, cols = 2, rCenter = 0, cCenter = 0
// Output: [[0,0],[0,1]]
// Explanation: The distances from (0, 0) to other cells are: [0,1]
//
// Constraints:
// 1 <= rows, cols <= 100
// 	0 <= rCenter < rows
// 	0 <= cCenter < cols
//

class Solution {
    public int[][] allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        int[][] result = new int[rows * cols][2];
        int index = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                result[index][0] = r;
                result[index][1] = c;
                index++;
            }
        }

        Arrays.sort(result, (a, b) -> {
            int distA = Math.abs(a[0] - rCenter) + Math.abs(a[1] - cCenter);
            int distB = Math.abs(b[0] - rCenter) + Math.abs(b[1] - cCenter);
            return Integer.compare(distA, distB);
        });

        return result;          
    }
}
