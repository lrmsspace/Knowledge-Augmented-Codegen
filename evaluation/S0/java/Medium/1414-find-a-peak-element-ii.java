// Source: https://leetcode.com/problems/find-a-peak-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
//
// Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
//
// You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
//
// You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
//
// Example:
// Input: mat = [[1,4],[3,2]]
// Output: [0,1]
// Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 500
// 	1 <= mat[i][j] <= 105
// 	No two adjacent cells are equal.
//

class Solution {
    public int[] findPeakGrid(int[][] mat) {
        int rows = mat.length;
        int cols = mat[0].length;

        int left = 0;
        int right = cols - 1;

        while (left <= right) {
            int midCol = left + (right - left) / 2;

            // Find the row index of the maximum element in the midCol
            int maxRow = 0;
            for (int r = 0; r < rows; r++) {
                if (mat[r][midCol] > mat[maxRow][midCol]) {
                    maxRow = r;
                }
            }

            // Check the neighbors
            boolean leftIsGreater = (midCol - 1 >= 0) && (mat[maxRow][midCol - 1] > mat[maxRow][midCol]);
            boolean rightIsGreater = (midCol + 1 < cols) && (mat[maxRow][midCol + 1] > mat[maxRow][midCol]);

            if (!leftIsGreater && !rightIsGreater) {
                // Found a peak
                return new int[]{maxRow, midCol};
            } else if (rightIsGreater) {
                // Move to the right half
                left = midCol + 1;
            } else {
                // Move to the left half
                right = midCol - 1;
            }
        }

        return new int[]{-1, -1}; // This line should never be reached          
    }
}
