// Source: https://leetcode.com/problems/path-with-minimum-effort/   |   Difficulty: Medium
//
// Problem Description:
// You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
//
// A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
//
// Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
//
// Example:
// Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
// Output: 2
// Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
// This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
//
// Constraints:
// rows == heights.length
// 	columns == heights[i].length
// 	1 <= rows, columns <= 100
// 	1 <= heights[i][j] <= 106
//

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int rows = heightsSize;
    int cols = heightsColSize[0];
    int left = 0, right = 1_000_000; // Maximum possible effort

    int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

    bool canReachDestination(int maxEffort) {
        bool visited[rows][cols];
        memset(visited, false, sizeof(visited));
        visited[0][0] = true;

        typedef struct {
            int row;
            int col;
        } Cell;

        Cell queue[rows * cols];
        int front = 0, back = 0;
        queue[back++] = (Cell){0, 0};

        while (front < back) {
            Cell current = queue[front++];
            if (current.row == rows - 1 && current.col == cols - 1) {
                return true;
            }

            for (int i = 0; i < 4; i++) {
                int newRow = current.row + directions[i][0];
                int newCol = current.col + directions[i][1];

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && !visited[newRow][newCol]) {
                    int effort = abs(heights[newRow][newCol] - heights[current.row][current.col]);
                    if (effort <= maxEffort) {
                        visited[newRow][newCol] = true;
                        queue[back++] = (Cell){newRow, newCol};
                    }
                }
            }
        }
        return false;
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canReachDestination(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;        
}
