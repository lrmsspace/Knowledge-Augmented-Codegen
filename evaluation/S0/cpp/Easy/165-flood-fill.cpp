// Source: https://leetcode.com/problems/flood-fill/   |   Difficulty: Easy
//
// Problem Description:
// You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. You are also given three integers sr, sc, and color. Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].
//
// To perform a flood fill:
//
//
// 	Begin with the starting pixel and change its color to color.
// 	Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.
// 	Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
// 	The process stops when there are no more adjacent pixels of the original color to update.
//
//
// Return the modified image after performing the flood fill.
//
// Example:
// Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
//
// Output: [[2,2,2],[2,2,0],[2,0,1]]
//
// Explanation:
//
//
//
// From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
//
// Note the bottom corner is not colored 2, because it is not horizontally or vertically connected to the starting pixel.
//
// Constraints:
// m == image.length
// 	n == image[i].length
// 	1 <= m, n <= 50
// 	0 <= image[i][j], color < 216
// 	0 <= sr < m
// 	0 <= sc < n
//

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];
        if (originalColor == color) {
            return image; // No need to fill if the color is the same
        }
        
        int rows = image.size();
        int cols = image[0].size();
        
        function<void(int, int)> dfs = [&](int r, int c) {
            // Check boundaries and if the current pixel matches the original color
            if (r < 0 || r >= rows || c < 0 || c >= cols || image[r][c] != originalColor) {
                return;
            }
            
            // Change the color of the current pixel
            image[r][c] = color;
            
            // Recursively call dfs for adjacent pixels
            dfs(r + 1, c); // Down
            dfs(r - 1, c); // Up
            dfs(r, c + 1); // Right
            dfs(r, c - 1); // Left
        };
        
        // Start DFS from the initial pixel
        dfs(sr, sc);
        
        return image;           
    }
};
