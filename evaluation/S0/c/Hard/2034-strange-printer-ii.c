// Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special requirements:
//
//
// 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
// 	Once the printer has used a color for the above operation, the same color cannot be used again.
//
//
// You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
//
// Return true if it is possible to print the matrix targetGrid, otherwise, return false.
//
// Example:
// Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
// Output: true
//
// Constraints:
// m == targetGrid.length
// 	n == targetGrid[i].length
// 	1 <= m, n <= 60
// 	1 <= targetGrid[row][col] <= 60
//

bool isPrintable(int** targetGrid, int targetGridSize, int* targetGridColSize) {
    int m = targetGridSize;
    int n = targetGridColSize[0];
    int top[61], bottom[61], left[61], right[61];
    memset(top, 0x3f, sizeof(top));
    memset(bottom, 0, sizeof(bottom));
    memset(left, 0x3f, sizeof(left));
    memset(right, 0, sizeof(right));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int color = targetGrid[i][j];
            if (i < top[color]) top[color] = i;
            if (i > bottom[color]) bottom[color] = i;
            if (j < left[color]) left[color] = j;
            if (j > right[color]) right[color] = j;
        }
    }

    int indegree[61] = {0};
    for (int color = 1; color <= 60; ++color) {
        if (top[color] == 0x3f3f3f3f) continue; /* color not present */
        for (int i = top[color]; i <= bottom[color]; ++i) {
            for (int j = left[color]; j <= right[color]; ++j) {
                int c2 = targetGrid[i][j];
                if (c2 != color) {
                    indegree[c2]++;
                }
            }
        }
    }

    int queue[61], front = 0, back = 0;
    for (int color = 1; color <= 60; ++color) {
        if (top[color] != 0x3f3f3f3f && indegree[color] == 0) {
            queue[back++] = color;
        }
    }

    int processed = 0;
    while (front < back) {
        int color = queue[front++];
        processed++;
        for (int i = top[color]; i <= bottom[color]; ++i) {
            for (int j = left[color]; j <= right[color]; ++j) {
                int c2 = targetGrid[i][j];
                if (c2 != color) {
                    indegree[c2]--;
                    if (indegree[c2] == 0) {
                        queue[back++] = c2;
                    }
                }
            }
        }
    }
    return processed == 60 - (int)(sizeof(indegree) / sizeof(indegree[0]) - 1 - (int)(sizeof(top) / sizeof(top[0])) + 1);
}

