// Source: https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. Your initial position is at the top-left cell (0, 0).
//
// Starting from the cell (i, j), you can move to one of the following cells:
//
//
// 	Cells (i, k) with j < k <= grid[i][j] + j (rightward movement), or
// 	Cells (k, j) with i < k <= grid[i][j] + i (downward movement).
//
//
// Return the minimum number of cells you need to visit to reach the bottom-right cell (m - 1, n - 1). If there is no valid path, return -1.
//
// Example:
// Input: grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
// Output: 4
// Explanation: The image above shows one of the paths that visits exactly 4 cells.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= grid[i][j] < m * n
// 	grid[m - 1][n - 1] == 0
//

class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> rowMax(n, -1);
        vector<int> colMax(m, -1);
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = 1;
        
        using PII = pair<int, int>;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({1, 0 * n + 0});
        
        while (!pq.empty()) {
            auto [d, pos] = pq.top();
            pq.pop();
            int i = pos / n;
            int j = pos % n;
            
            if (d > dist[i][j]) continue;
            
            // Move right
            for (int nj = max(j + 1, rowMax[i] + 1); nj <= min(n - 1, j + grid[i][j]); nj++) {
                if (dist[i][nj] > dist[i][j] + 1) {
                    dist[i][nj] = dist[i][j] + 1;
                    pq.push({dist[i][nj], i * n + nj});
                }
            }
            rowMax[i] = max(rowMax[i], min(n - 1, j + grid[i][j]));
            
            // Move down
            for (int ni = max(i + 1, colMax[j] + 1); ni <= min(m - 1, i + grid[i][j]); ni++) {
                if (dist[ni][j] > dist[i][j] + 1) {
                    dist[ni][j] = dist[i][j] + 1;
                    pq.push({dist[ni][j], ni * n + j});
                }
            }
            colMax[j] = max(colMax[j], min(m - 1, i + grid[i][j]));
        }
        
        return dist[m - 1][n - 1] == INT_MAX ? -1 : dist[m - 1][n - 1];         
    }
};
