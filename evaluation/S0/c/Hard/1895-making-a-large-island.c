// Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
//
// Return the size of the largest island in grid after applying this operation.
//
// An island is a 4-directionally connected group of 1s.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 500
// 	grid[i][j] is either 0 or 1.
//

int largestIsland(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int *area = (int*)calloc(n * n + 2, sizeof(int)); /* area[island_id] = area */
    if (!area) return 0;
    int island_id = 2; /* start from 2 to distinguish from 0 and 1 */

    /* DFS to label islands and calculate their areas */
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                /* Start DFS */
                int stackSize = n * n;
                int (*stack)[2] = malloc(stackSize * sizeof(*stack));
                if (!stack) { free(area); return 0; }
                int top = 0;
                stack[top][0] = i; stack[top][1] = j; top++;
                grid[i][j] = island_id;
                int current_area = 0;

                while (top > 0) {
                    top--;
                    int x = stack[top][0];
                    int y = stack[top][1];
                    current_area++;

                    for (int d = 0; d < 4; ++d) {
                        int nx = x + directions[d][0];
                        int ny = y + directions[d][1];
                        if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                            grid[nx][ny] = island_id;
                            stack[top][0] = nx; stack[top][1] = ny; top++;
                        }
                    }
                }
                area[island_id] = current_area;
                island_id++;
                free(stack);
            }
        }
    }

    int max_area = 0;
    for (int id = 2; id < island_id; ++id) {
        if (area[id] > max_area) max_area = area[id];
    }

    /* Check each zero cell to see potential island size */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                int seen[island_id];
                memset(seen, 0, sizeof(seen));
                int potential_area = 1; /* flip this 0 to 1 */

                for (int d = 0; d < 4; ++d) {
                    int nx = i + directions[d][0];
                    int ny = j + directions[d][1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        int neighbor_id = grid[nx][ny];
                        if (neighbor_id > 1 && !seen[neighbor_id]) {
                            potential_area += area[neighbor_id];
                            seen[neighbor_id] = 1;
                        }
                    }
                }
                if (potential_area > max_area) {
                    max_area = potential_area;
                }
            }
        }
    }
    free(area);
    return max_area;
}
