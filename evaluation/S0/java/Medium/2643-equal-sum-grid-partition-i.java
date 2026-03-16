// Source: https://leetcode.com/problems/equal-sum-grid-partition-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
//
//
// 	Each of the two resulting sections formed by the cut is non-empty.
// 	The sum of the elements in both sections is equal.
//
//
// Return true if such a partition exists; otherwise return false.
//
// Example:
// Input: grid = [[1,4],[2,3]]
//
// Output: true
//
// Explanation:
//
//
//
// A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.
//
// Constraints:
// 1 <= m == grid.length <= 105
// 	1 <= n == grid[i].length <= 105
// 	2 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

class Solution {
    public boolean canPartitionGrid(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        // Check for horizontal cut
        int[] rowSums = new int[m];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowSums[i] += grid[i][j];
            }
        }

        int totalSum = 0;
        for (int sum : rowSums) {
            totalSum += sum;
        }

        int runningSum = 0;
        for (int i = 0; i < m - 1; i++) {
            runningSum += rowSums[i];
            if (runningSum * 2 == totalSum) {
                return true;
            }
        }

        // Check for vertical cut
        int[] colSums = new int[n];
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                colSums[j] += grid[i][j];
            }
        }

        totalSum = 0;
        for (int sum : colSums) {
            totalSum += sum;
        }

        runningSum = 0;
        for (int j = 0; j < n - 1; j++) {
            runningSum += colSums[j];
            if (runningSum * 2 == totalSum) {
                return true;
            }
        }

        return false;           
    }
}
