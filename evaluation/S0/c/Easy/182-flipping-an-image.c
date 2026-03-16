// Source: https://leetcode.com/problems/flipping-an-image/   |   Difficulty: Easy
//
// Problem Description:
// Given an n x n binary matrix image, flip the image horizontally, then invert it, and return the resulting image.
//
// To flip an image horizontally means that each row of the image is reversed.
//
//
// 	For example, flipping [1,1,0] horizontally results in [0,1,1].
//
//
// To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0.
//
//
// 	For example, inverting [0,1,1] results in [1,0,0].
//
// Example:
// Input: image = [[1,1,0],[1,0,1],[0,0,0]]
// Output: [[1,0,0],[0,1,0],[1,1,1]]
// Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
// Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
//
// Constraints:
// n == image.length
// 	n == image[i].length
// 	1 <= n <= 20
// 	images[i][j] is either 0 or 1.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** flipAndInvertImage(int** image, int imageSize, int* imageColSize, int* returnSize, int** returnColumnSizes) {
    int i, j, temp;
    *returnSize = imageSize;
    *returnColumnSizes = (int*)malloc(imageSize * sizeof(int));
    for (i = 0; i < imageSize; i++) {
        (*returnColumnSizes)[i] = imageColSize[i];
        for (j = 0; j < (imageColSize[i] + 1) / 2; j++) {
            // Swap and invert
            temp = image[i][j] ^ 1;
            image[i][j] = image[i][imageColSize[i] - 1 - j] ^ 1;
            image[i][imageColSize[i] - 1 - j] = temp;
        }
        // If the row has an odd number of elements, invert the middle one
        if (imageColSize[i] % 2 == 1) {
            image[i][imageColSize[i] / 2] ^= 1;
        }
    }
    return image;       
}
