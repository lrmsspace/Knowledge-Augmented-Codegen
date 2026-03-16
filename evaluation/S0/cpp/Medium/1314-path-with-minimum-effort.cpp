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

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
        effort[0][0] = 0;

        using Cell = pair<int, pair<int, int>>; // (effort, (row, col))
        priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
        pq.push({0, {0, 0}});

        vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

        while (!pq.empty()) {
            auto [currEffort, pos] = pq.top();
            pq.pop();
            int r = pos.first;
            int c = pos.second;

            if (r == rows - 1 && c == cols - 1) {
                return currEffort;
            }

            for (const auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    int nextEffort = max(currEffort, abs(heights[nr][nc] - heights[r][c]));
                    if (nextEffort < effort[nr][nc]) {
                        effort[nr][nc] = nextEffort;
                        pq.push({nextEffort, {nr, nc}});
                    }
                }
            }
        }

        return 0; // This line should never be reached          
    }
};
