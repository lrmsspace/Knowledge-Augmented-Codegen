// Source: https://leetcode.com/problems/image-smoother/   |   Difficulty: Easy
//
// Problem Description:
// An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by rounding down the average of the cell and the eight surrounding cells (i.e., the average of the nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).
//
// Given an m x n integer matrix img representing the grayscale of an image, return the image after applying the smoother on each cell of it.
//
// Example:
// Input: img = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[0,0,0],[0,0,0],[0,0,0]]
// Explanation:
// For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
// For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
// For the point (1,1): floor(8/9) = floor(0.88888889) = 0
//
// Constraints:
// m == img.length
// 	n == img[i].length
// 	1 <= m, n <= 200
// 	0 <= img[i][j] <= 255
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** imageSmoother(int** img, int imgSize, int* imgColSize, int* returnSize, int** returnColumnSizes) {
    int directions[9][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},  {0, 0},  {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    
    int** result = (int**)malloc(imgSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(imgSize * sizeof(int));
    *returnSize = imgSize;
    
    for (int i = 0; i < imgSize; i++) {
        result[i] = (int*)malloc(imgColSize[i] * sizeof(int));
        (*returnColumnSizes)[i] = imgColSize[i];
        
        for (int j = 0; j < imgColSize[i]; j++) {
            int sum = 0;
            int count = 0;
            
            for (int d = 0; d < 9; d++) {
                int newRow = i + directions[d][0];
                int newCol = j + directions[d][1];
                
                if (newRow >= 0 && newRow < imgSize && newCol >= 0 && newCol < imgColSize[i]) {
                    sum += img[newRow][newCol];
                    count++;
                }
            }
            
            result[i][j] = sum / count;
        }
    }
    
    return result;      
}
