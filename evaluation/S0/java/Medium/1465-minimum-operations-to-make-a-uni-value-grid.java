// Source: https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.
//
// A uni-value grid is a grid where all the elements of it are equal.
//
// Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.
//
// Example:
// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following: 
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= x, grid[i][j] <= 104
//

class Solution {
    public int minOperations(int[][] grid, int x) {
        int m = grid.length;
        int n = grid[0].length;
        int size = m * n;
        int[] arr = new int[size];
        int index = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                arr[index++] = grid[i][j];
            }
        }
        Arrays.sort(arr);
        int median = arr[size / 2];
        int operations = 0;
        for (int value : arr) {
            int diff = Math.abs(value - median);
            if (diff % x != 0) {
                return -1;
            }
            operations += diff / x;
        }
        return operations;          
    }
}
