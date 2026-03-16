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

public:

    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {

        
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> result = grid;

        int layers = min(m, n) / 2;

        for (int layer = 0; layer < layers; ++layer) {
            int top = layer;
            int bottom = m - layer - 1;
            int left = layer;
            int right = n - layer - 1;

            vector<int> elements;

            // Extract the elements of the current layer
            for (int j = left; j <= right; ++j) elements.push_back(grid[top][j]);
            for (int i = top + 1; i <= bottom; ++i) elements.push_back(grid[i][right]);
            for (int j = right - 1; j >= left; --j) elements.push_back(grid[bottom][j]);
            for (int i = bottom - 1; i > top; --i) elements.push_back(grid[i][left]);

            int perimeter = elements.size();
            int rotation = k % perimeter;

            // Rotate the elements
            vector<int> rotatedElements(perimeter);
            for (int i = 0; i < perimeter; ++i) {
                rotatedElements[i] = elements[(i + rotation) % perimeter];
            }

            // Place the rotated elements back into the result grid
            int index = 0;
            for (int j = left; j <= right; ++j) result[top][j] = rotatedElements[index++];
            for (int i = top + 1; i <= bottom; ++i) result[i][right] = rotatedElements[index++];
            for (int j = right - 1; j >= left; --j) result[bottom][j] = rotatedElements[index++];
            for (int i = bottom - 1; i > top; --i) result[i][left] = rotatedElements[index++];
        }

        return result;
    }

};
