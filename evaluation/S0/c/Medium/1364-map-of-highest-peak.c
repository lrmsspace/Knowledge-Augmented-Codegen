// Source: https://leetcode.com/problems/map-of-highest-peak/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer matrix isWater of size m x n that represents a map of land and water cells.
//
//
// 	If isWater[i][j] == 0, cell (i, j) is a land cell.
// 	If isWater[i][j] == 1, cell (i, j) is a water cell.
//
//
// You must assign each cell a height in a way that follows these rules:
//
//
// 	The height of each cell must be non-negative.
// 	If the cell is a water cell, its height must be 0.
// 	Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
//
// Find an assignment of heights such that the maximum height in the matrix is maximized.
//
// Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.
//
// Example:
// Input: isWater = [[0,1],[0,0]]
// Output: [[1,0],[2,1]]
// Explanation: The image shows the assigned heights of each cell.
// The blue cell is the water cell, and the green cells are the land cells.
//
// Constraints:
// m == isWater.length
// 	n == isWater[i].length
// 	1 <= m, n <= 1000
// 	isWater[i][j] is 0 or 1.
// 	There is at least one water cell.
//
//
//  
// Note: This question is the same as 542: https://leetcode.com/problems/01-matrix/
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** highestPeak(int** isWater, int isWaterSize, int* isWaterColSize, int* returnSize, int** returnColumnSizes) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int** heights = (int**)malloc(isWaterSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(isWaterSize * sizeof(int));
    *returnSize = isWaterSize;
    for (int i = 0; i < isWaterSize; i++) {
        heights[i] = (int*)malloc(isWaterColSize[i] * sizeof(int));
        (*returnColumnSizes)[i] = isWaterColSize[i];
        for (int j = 0; j < isWaterColSize[i]; j++) {
            heights[i][j] = -1; // Initialize heights to -1
        }
    }

    typedef struct {
        int x;
        int y;
    } Point;

    Point* queue = (Point*)malloc(isWaterSize * (*returnColumnSizes)[0] * sizeof(Point));
    int front = 0, rear = 0;

    // Enqueue all water cells and set their height to 0
    for (int i = 0; i < isWaterSize; i++) {
        for (int j = 0; j < isWaterColSize[i]; j++) {
            if (isWater[i][j] == 1) {
                heights[i][j] = 0;
                queue[rear++] = (Point){i, j};
            }
        }
    }

    // BFS to assign heights to land cells
    while (front < rear) {
        Point p = queue[front++];
        for (int d = 0; d < 4; d++) {
            int newX = p.x + directions[d][0];
            int newY = p.y + directions[d][1];
            if (newX >= 0 && newX < isWaterSize && newY >= 0 && newY < isWaterColSize[0] && heights[newX][newY] == -1) {
                heights[newX][newY] = heights[p.x][p.y] + 1;
                queue[rear++] = (Point){newX, newY};
            }
        }
    }

    free(queue);
    return heights;     
}
