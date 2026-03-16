// Source: https://leetcode.com/problems/last-day-where-you-can-still-cross/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col representing the number of rows and columns in the matrix, respectively.
//
// Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) will be covered with water (i.e., changed to 1).
//
// You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal directions (left, right, up, and down).
//
// Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.
//
// Example:
// Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
// Output: 2
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 2.
//
// Constraints:
// 2 <= row, col <= 2 * 104
// 	4 <= row * col <= 2 * 104
// 	cells.length == row * col
// 	1 <= ri <= row
// 	1 <= ci <= col
// 	All the values of cells are unique.
//

int latestDayToCross(int row, int col, int** cells, int cellsSize, int* cellsColSize) {
    int left = 1, right = cellsSize;
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

    int canCross(int day) {
        int *grid = (int*)calloc(row * col, sizeof(int));
        if (!grid) return 0;

        for (int i = 0; i < day; ++i) {
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;
            grid[r * col + c] = 1; /* mark as water */
        }

        int *visited = (int*)calloc(row * col, sizeof(int));
        if (!visited) { free(grid); return 0; }

        int stackSize = row * col;
        int *stack = (int*)malloc(stackSize * sizeof(int));
        if (!stack) { free(grid); free(visited); return 0; }

        for (int c = 0; c < col; ++c) {
            if (grid[c] == 0) { /* land */
                stack[0] = c;
                visited[c] = 1;
                int sp = 1;
                while (sp > 0) {
                    int pos = stack[--sp];
                    int r = pos / col;
                    int cc = pos % col;
                    if (r == row - 1) { /* reached bottom */
                        free(grid); free(visited); free(stack);
                        return 1;
                    }
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + directions[d][0];
                        int nc = cc + directions[d][1];
                        if (nr >= 0 && nr < row && nc >= 0 && nc < col) {
                            int npos = nr * col + nc;
                            if (grid[npos] == 0 && !visited[npos]) {
                                visited[npos] = 1;
                                stack[sp++] = npos;
                            }
                        }
                    }
                }
            }
        }

        free(grid); free(visited); free(stack);
        return 0;
    }

    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (can     
}
