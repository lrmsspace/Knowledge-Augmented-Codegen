// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
//
// Problem Description:
// In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
//
// In one move the snake can:
//
//
// 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
// 	
// 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
// 	
//
//
// Return the minimum number of moves to reach the target.
//
// If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [[0,0,0,0,0,1],
//                [1,1,0,0,1,0],
//                [0,0,0,0,1,1],
//                [0,0,1,0,1,0],
//                [0,1,1,0,0,0],
//                [0,1,1,0,0,0]]
// Output: 11
// Explanation:
// One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
//
// Constraints:
// 2 <= n <= 100
// 	0 <= grid[i][j] <= 1
// 	It is guaranteed that the snake starts at empty cells.
//

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<vector<int>>> dist(n, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
        dist[0][1][0] = 0;  // (row, col, orientation) orientation: 0 - horizontal, 1 - vertical
        
        queue<tuple<int, int, int>> q;
        q.push({0, 1, 0});
        
        int directions[4][3] = {
            {0, 1, 0},   // Move right
            {1, 0, 0},   // Move down
            {0, 0, 1},   // Rotate clockwise
            {0, 0, -1}   // Rotate counterclockwise
        };
        
        while (!q.empty()) {
            auto [r, c, o] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                int no = o;
                
                if (dir[2] == 1) { // Rotate clockwise
                    if (o == 0 && r + 1 < n && grid[r + 1][c - 1] == 0 && grid[r + 1][c] == 0) {
                        no = 1;
                    } else {
                        continue;
                    }
                } else if (dir[2] == -1) { // Rotate counterclockwise
                    if (o == 1 && c + 1 < n && grid[r - 1][c + 1] == 0 && grid[r][c + 1] == 0) {
                        no = 0;
                    } else {
                        continue;
                    }
                }
                
                if (no == 0) { // Horizontal
                    if (nc < n && grid[nr][nc] == 0 && grid[nr][nc - 1] == 0) {
                        if (dist[nr][nc][no] > dist[r][c][o] + 1) {
                            dist[nr][nc][no] = dist[r][c][o] + 1;
                            q.push({nr, nc, no});
                        }
                    }
                } else { // Vertical
                    if (nr < n && grid[nr][nc] == 0 && grid[nr - 1][nc] == 0) {
                        if (dist[nr][nc][no] > dist[r][c][o] + 1) {
                            dist[nr][nc][no] = dist[r][c][o] + 1;
                            q.push({nr, nc, no});
                        }
                    }
                }
            }
        }
        return dist[n - 1][n - 1][0] == INT_MAX ? -1 : dist[n - 1][n - 1][0];      
    }
};
