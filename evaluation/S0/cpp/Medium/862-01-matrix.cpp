// Source: https://leetcode.com/problems/01-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
//
// The distance between two cells sharing a common edge is 1.
//
// Example:
// Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
// Output: [[0,0,0],[0,1,0],[0,0,0]]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	mat[i][j] is either 0 or 1.
// 	There is at least one 0 in mat.
//
//
//  
// Note: This question is the same as 1765: https://leetcode.com/problems/map-of-highest-peak/
//

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX - 10000));
        queue<pair<int, int>> q;

        // Initialize the queue with all 0 cells
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // Directions for moving up, down, left, right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // BFS to update distances
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (const auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;

                // Check bounds and if we can update the distance
                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                    if (dist[newX][newY] > dist[x][y] + 1) {
                        dist[newX][newY] = dist[x][y] + 1;
                        q.push({newX, newY});
                    }
                }
            }
        }

        return dist;            
    }
};
