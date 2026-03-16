// Source: https://leetcode.com/problems/rotating-the-box/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:
//
//
// 	A stone '#'
// 	A stationary obstacle '*'
// 	Empty '.'
//
//
// The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.
//
// It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.
//
// Return an n x m matrix representing the box after the rotation described above.
//
// Example:
// Input: boxGrid = [["#",".","#"]]
// Output: [["."],
//          ["#"],
//          ["#"]]
//
// Constraints:
// m == boxGrid.length
// 	n == boxGrid[i].length
// 	1 <= m, n <= 500
// 	boxGrid[i][j] is either '#', '*', or '.'.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** rotateTheBox(char** boxGrid, int boxGridSize, int* boxGridColSize, int* returnSize, int** returnColumnSizes) {
    int m = boxGridSize;
    int n = boxGridColSize[0];
    
    // Allocate memory for the rotated box
    char** rotatedBox = (char**)malloc(n * sizeof(char*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        rotatedBox[i] = (char*)malloc(m * sizeof(char));
        (*returnColumnSizes)[i] = m;
    }
    
    // Rotate the box 90 degrees clockwise
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            rotatedBox[j][m - 1 - i] = boxGrid[i][j];
        }
    }
    
    // Apply gravity to the stones in the rotated box
    for (int j = 0; j < n; j++) {
        int emptySpot = m - 1; // Start from the bottom of the column
        for (int i = m - 1; i >= 0; i--) {
            if (rotatedBox[j][i] == '*') {
                emptySpot = i - 1; // Update empty spot above the obstacle
            } else if (rotatedBox[j][i] == '#') {
                if (i != emptySpot) {
                    rotatedBox[j][emptySpot] = '#';
                    rotatedBox[j][i] = '.';
                }
                emptySpot--; // Move the empty spot up after placing a stone
            }
        }
    }
    
    *returnSize = n;
    return rotatedBox;      
}
