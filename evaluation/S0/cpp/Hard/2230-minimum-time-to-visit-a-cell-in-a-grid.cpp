// Source: https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].
//
// You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1 second.
//
// Return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.
//
// Example:
// Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
// Output: 7
// Explanation: One of the paths that we can take is the following:
// - at t = 0, we are on the cell (0,0).
// - at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
// - at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
// - at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
// - at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
// - at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
// - at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
// - at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
// The final time is 7. It can be shown that it is the minimum time possible.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	0 <= grid[i][j] <= 105
// 	grid[0][0] == 0
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//

class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = 0;
        
        using T = pair<int, pair<int, int>>;
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({0, {0, 0}});
        
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        while (!pq.empty()) {
            auto [time, cell] = pq.top();
            pq.pop();
            int x = cell.first;
            int y = cell.second;
            
            if (x == m - 1 && y == n - 1) {
                return time;
            }
            
            for (auto& dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    int arrivalTime = max(time + 1, grid[nx][ny]);
                    // Ensure parity condition
                    if ((arrivalTime - grid[nx][ny]) % 2 != 0) {
                        arrivalTime++;
                    }
                    
                    if (arrivalTime < dist[nx][ny]) {
                        dist[nx][ny] = arrivalTime;
                        pq.push({arrivalTime, {nx, ny}});
                    }
                }
            }
        }
        
        return -1;          
    }
};
