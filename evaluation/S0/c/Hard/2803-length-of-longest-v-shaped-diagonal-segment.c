// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
//
// A V-shaped diagonal segment is defined as:
//
//
// 	The segment starts with 1.
// 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
// 	The segment:
// 	
// 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// 		Continues the sequence in the same diagonal direction.
// 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
// 	
// 	
//
//
// Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
//
// Example:
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
//
// Output: 5
//
// Explanation:
//
//
//
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
//
// Constraints:
// n == grid.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	grid[i][j] is either 0, 1 or 2.
//

int lenOfVDiagonal(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize, m = gridColSize[0];
    int dp1[n][m][4]; // four directions
    memset(dp1, 0, sizeof(dp1));
    int res = 0;

    // direction 0: top-left to bottom-right
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 1) dp1[i][j][0] = 1;
            else if (grid[i][j] == 2 && i > 0 && j > 0 && dp1[i-1][j-1][0] > 0)
                dp1[i][j][0] = dp1[i-1][j-1][0] + 1;
            else if (grid[i][j] == 0 && i > 0 && j > 0 && dp1[i-1][j-1][0] > 1)
                dp1[i][j][0] = dp1[i-1][j-1][0] + 1;
        }
    }

    // direction 1: top-right to bottom-left
    for (int i = 0; i < n; ++i) {
        for (int j = m - 1; j >= 0; --j) {
            if (grid[i][j] == 1) dp1[i][j][1] = 1;
            else if (grid[i][j] == 2 && i > 0 && j < m - 1 && dp1[i-1][j+1][1] > 0)
                dp1[i][j][1] = dp1[i-1][j+1][1] + 1;
            else if (grid[i][j] == 0 && i > 0 && j < m - 1 && dp1[i-1][j+1][1] > 1)
                dp1[i][j][1] = dp1[i-1][j+1][1] + 1;
        }
    }

    // direction 2: bottom-left to top-right
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 1) dp1[i][j][2] = 1;
            else if (grid[i][j] == 2 && i < n - 1 && j > 0 && dp1[i+1][j-1][2] > 0)
                dp1[i][j][2] = dp1[i+1][j-1][2] + 1;
            else if (grid[i][j] == 0 && i < n - 1 && j > 0 && dp1[i+1][j-1][2] > 1)
                dp1[i][j][2] = dp1[i+1][j-1][2] + 1;
        }
    }
    // direction 3: bottom-right to top-left
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (grid[i][j] == 1) dp1[i][j][3] = 1;
            else if (grid[i][j] == 2 && i < n - 1 && j < m - 1 && dp1[i+1][j+1][3] > 0)
                dp1[i][j][3] = dp1[i+1][j+1][3] + 1;
            else if (grid[i][j] == 0 && i < n - 1 && j < m - 1 && dp1[i+1][j+1][3] > 1)
                dp1[i][j][3] = dp1[i+1][j+1][3] + 1;
        }
    }
    // combine two directions with a 90-degree turn
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // direction 0 to 1
            if (dp1[i][j][0] > 0 && dp1[i][j][1] > 0) {
                int len = dp1[i][j][0] + dp1[i][j][1] - 1;
                if (len > res) res = len;
            }
            // direction 1 to 3
            if (dp1[i][j][1] > 0 && dp1[i][j][3] > 0) {
                int len = dp1[i][j][1] + dp1[i][j][3] - 1;
                if (len > res) res = len;
            }
            // direction 3 to 2
            if (dp1[i][j][3] > 0 && dp1[i][j][2] > 0) {
                int len = dp1[i][j][3] + dp1[i][j][2] - 1;
                if (len > res) res = len;
            }
            // direction 2 to 0
            if (dp1[i][j][2] > 0 && dp1[i][j][0] > 0) {
                int len = dp1[i][j][2] + dp1[i][j][0] - 1;
                if (len > res) res = len;
            }
        }
    }
    return res;
}
