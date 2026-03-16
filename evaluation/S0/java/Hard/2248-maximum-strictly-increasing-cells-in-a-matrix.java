// Source: https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.
//
// From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.
//
// Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.
//
// Return an integer denoting the maximum number of cells that can be visited.
//
// Example:
// Input: mat = [[3,1],[3,4]]
// Output: 2
// Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2.
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	-105 <= mat[i][j] <= 105
//

class Solution {
    public int maxIncreasingCells(int[][] mat) {
        int m = mat.length, n = mat[0].length;
        int[][] dp = new int[m][n];
        Map<Integer, List<int[]>> map = new TreeMap<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                map.putIfAbsent(mat[i][j], new ArrayList<>());
                map.get(mat[i][j]).add(new int[]{i, j});
            }
        }

        int[] rowMax = new int[m];
        int[] colMax = new int[n];
        int result = 1;

        for (int key : map.keySet()) {
            List<int[]> positions = map.get(key);
            for (int[] pos : positions) {
                int i = pos[0], j = pos[1];
                dp[i][j] = Math.max(rowMax[i], colMax[j]) + 1;
                result = Math.max(result, dp[i][j]);
            }
            for (int[] pos : positions) {
                int i = pos[0], j = pos[1];
                rowMax[i] = Math.max(rowMax[i], dp[i][j]);
                colMax[j] = Math.max(colMax[j], dp[i][j]);
            }
        }

        return result;          
    }
}
