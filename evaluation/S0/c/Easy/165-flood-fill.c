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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes) {
    int originalColor = image[sr][sc];
    if (originalColor == color) {
        *returnSize = imageSize;
        *returnColumnSizes = (int*)malloc(imageSize * sizeof(int));
        for (int i = 0; i < imageSize; i++) {
            (*returnColumnSizes)[i] = imageColSize[i];
        }
        return image;
    }

    void dfs(int r, int c) {
        if (r < 0 || r >= imageSize || c < 0 || c >= imageColSize[0] || image[r][c] != originalColor) {
            return;
        }
        image[r][c] = color;
        dfs(r + 1, c);
        dfs(r - 1, c);
        dfs(r, c + 1);
        dfs(r, c - 1);
    }

    dfs(sr, sc);

    *returnSize = imageSize;
    *returnColumnSizes = (int*)malloc(imageSize * sizeof(int));
    for (int i = 0; i < imageSize; i++) {
        (*returnColumnSizes)[i] = imageColSize[i];
    }
    return image;       
}
