// Source: https://leetcode.com/problems/shortest-path-in-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
//
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
//
//
// 	All the visited cells of the path are 0.
// 	All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
//
//
// The length of a clear path is the number of visited cells of this path.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 2
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }

        vector<pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},          {0, 1},
            {1, -1}, {1, 0}, {1, 1}
        };

        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 1; // Mark as visited with distance 1

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            int dist = grid[x][y];

            if (x == n - 1 && y == n - 1) {
                return dist;
            }

            for (const auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;

                if (newX >= 0 && newX < n && newY >= 0 && newY < n && grid[newX][newY] == 0) {
                    grid[newX][newY] = dist + 1; // Mark as visited with distance
                    q.push({newX, newY});
                }
            }
        }

        return -1;          
    }
};
