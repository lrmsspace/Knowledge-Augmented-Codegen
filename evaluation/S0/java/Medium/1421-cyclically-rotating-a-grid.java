// Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
//
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
//
// Return the matrix after applying k cyclic rotations to it.
//
// Example:
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 50
// 	Both m and n are even integers.
// 	1 <= grid[i][j] <= 5000
// 	1 <= k <= 109
//

class Solution {

    public int[][] rotateGrid(int[][] grid, int k) {

        
        int m = grid.length;
        int n = grid[0].length;
        int layers = Math.min(m, n) / 2;

        for (int layer = 0; layer < layers; layer++) {
            int top = layer;
            int bottom = m - 1 - layer;
            int left = layer;
            int right = n - 1 - layer;

            List<Integer> elements = new ArrayList<>();

            // Extract the elements of the current layer
            for (int j = left; j <= right; j++) elements.add(grid[top][j]);
            for (int i = top + 1; i <= bottom; i++) elements.add(grid[i][right]);
            for (int j = right - 1; j >= left; j--) elements.add(grid[bottom][j]);
            for (int i = bottom - 1; i > top; i--) elements.add(grid[i][left]);

            int layerSize = elements.size();
            int rotations = k % layerSize;

            // Rotate the elements
            Collections.rotate(elements, -rotations);

            // Place the rotated elements back into the grid
            int index = 0;
            for (int j = left; j <= right; j++) grid[top][j] = elements.get(index++);
            for (int i = top + 1; i <= bottom; i++) grid[i][right] = elements.get(index++);
            for (int j = right - 1; j >= left; j--) grid[bottom][j] = elements.get(index++);
            for (int i = bottom - 1; i > top; i--) grid[i][left] = elements.get(index++);
        }

        return grid;
    }

}
