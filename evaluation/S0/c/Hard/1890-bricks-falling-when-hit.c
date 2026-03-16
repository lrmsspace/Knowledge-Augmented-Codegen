// Source: https://leetcode.com/problems/bricks-falling-when-hit/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary grid, where each 1 represents a brick and 0 represents an empty space. A brick is stable if:
//
//
// 	It is directly connected to the top of the grid, or
// 	At least one other brick in its four adjacent cells is stable.
//
//
// You are also given an array hits, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location hits[i] = (rowi, coli). The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).
//
// Return an array result, where each result[i] is the number of bricks that will fall after the ith erasure is applied.
//
// Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.
//
// Example:
// Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
// Output: [2]
// Explanation: Starting with the grid:
// [[1,0,0,0],
//  [1,1,1,0]]
// We erase the underlined brick at (1,0), resulting in the grid:
// [[1,0,0,0],
//  [0,1,1,0]]
// The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
// [[1,0,0,0],
//  [0,0,0,0]]
// Hence the result is [2].
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 200
// 	grid[i][j] is 0 or 1.
// 	1 <= hits.length <= 4 * 104
// 	hits[i].length == 2
// 	0 <= xi <= m - 1
// 	0 <= yi <= n - 1
// 	All (xi, yi) are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* hitBricks(int** grid, int gridSize, int* gridColSize, int** hits, int hitsSize, int* hitsColSize, int* returnSize) {
    int m = gridSize;
    int n = gridColSize[0];
    *returnSize = hitsSize;
    int* result = (int*)calloc(hitsSize, sizeof(int));

    // Directions for adjacent cells
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // Function to check if a cell is within bounds
    int isValid(int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    }

    // DFS to mark stable bricks
    void dfs(int x, int y, int** visited) {
        visited[x][y] = 1;
        for (int d = 0; d < 4; d++) {
            int newX = x + directions[d][0];
            int newY = y + directions[d][1];
            if (isValid(newX, newY) && grid[newX][newY] == 1 && !visited[newX][newY]) {
                dfs(newX, newY, visited);
            }
        }
    }

    // Mark all stable bricks after all hits
    for (int i = 0; i < hitsSize; i++) {
        int x = hits[i][0];
        int y = hits[i][1];
        if (grid[x][y] == 1) {
            grid[x][y] = 0; // Temporarily remove the brick
        }
    }

    int** visited = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        visited[i] = (int*)calloc(n, sizeof(int));
    }

    for (int j = 0; j < n; j++) {
        if (grid[0][j] == 1 && !visited[0][j]) {
            dfs(0, j, visited);
        }
    }

    // Process hits in reverse order
    for (int i = hitsSize - 1; i >= 0; i--) {
        int x = hits[i][0];
        int y = hits[i][1];
        if (grid[x][y] == 0) {
            grid[x][y] = 1; // Restore the brick
            int stableBefore = 0;
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    if (visited[r][c]) {
                        stableBefore++;
                    }
                }
            }

            // Check if the restored brick is stable
            int isStable = (x == 0);
            for (int d = 0; d < 4; d++) {
                int newX = x + directions[d][0];
                int newY = y + directions[d][1];
                if (isValid(newX, newY) && visited[newX][newY]) {
                    isStable = 1;
                    break;
                }
            }

            if (isStable) {
                dfs(x, y, visited);
            }

            int stableAfter = 0;
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    if (visited[r][c]) {
                        stableAfter++;
                    }
                }
            }

            result[i] = stableAfter - stableBefore - 1; // Exclude the restored brick
        }
    }
    for (int i = 0; i < m; i++) {
        free(visited[i]);
    }
    free(visited);
    return result;
}
