// Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
//
//
// 	'.' representing an empty cell.
// 	'#' representing an obstacle.
// 	An uppercase letter ('A'-'Z') representing a teleportation portal.
//
//
// You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
//
// If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
//
// Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
//
// Example:
// Input: matrix = ["A..",".A.","..."]
//
// Output: 2
//
// Explanation:
//
//
//
//
// 	Before the first move, teleport from (0, 0) to (1, 1).
// 	In the first move, move from (1, 1) to (1, 2).
// 	In the second move, move from (1, 2) to (2, 2).
//
// Constraints:
// 1 <= m == matrix.length <= 103
// 	1 <= n == matrix[i].length <= 103
// 	matrix[i][j] is either '#', '.', or an uppercase English letter.
// 	matrix[0][0] is not an obstacle.
//

class Solution {
public:
    int minMoves(vector<string>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (matrix[0][0] == '#' || matrix[m-1][n-1] == '#') return -1;

        unordered_map<char, vector<pair<int, int>>> portals;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                char cell = matrix[i][j];
                if (cell >= 'A' && cell <= 'Z') {
                    portals[cell].emplace_back(i, j);
                }
            }
        }

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        visited[0][0] = true;
        int moves = 0;

        vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();

                if (x == m - 1 && y == n - 1) return moves;

                for (const auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                        matrix[nx][ny] != '#' && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        q.emplace(nx, ny);
                    }
                }

                char cell = matrix[x][y];
                if (cell >= 'A' && cell <= 'Z' && portals.count(cell)) {
                    for (const auto& [px, py] : portals[cell]) {
                        if (!visited[px][py]) {
                            visited[px][py] = true;
                            q.emplace(px, py);
                        }
                    }
                    portals.erase(cell);
                }
            }
            moves++;
        }

        return -1;          
    }
};
