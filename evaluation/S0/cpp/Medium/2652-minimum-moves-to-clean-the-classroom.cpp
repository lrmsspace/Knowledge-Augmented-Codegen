// Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
//
//
// 	'S': Starting position of the student
// 	'L': Litter that must be collected (once collected, the cell becomes empty)
// 	'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
// 	'X': Obstacle the student cannot pass through
// 	'.': Empty space
//
//
// You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.
//
// Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
//
// Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
//
// Example:
// Input: classroom = ["S.", "XL"], energy = 2
//
// Output: 2
//
// Explanation:
//
//
// 	The student starts at cell (0, 0) with 2 units of energy.
// 	Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
// 	A valid sequence of moves to collect all litter is as follows:
// 	
// 		Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
// 		Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
// 	
// 	
// 	The student collects all the litter using 2 moves. Thus, the output is 2.
//
// Constraints:
// 1 <= m == classroom.length <= 20
// 	1 <= n == classroom[i].length <= 20
// 	classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
// 	1 <= energy <= 50
// 	There is exactly one 'S' in the grid.
// 	There are at most 10 'L' cells in the grid.
//

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        vector<pair<int, int>> litterPositions;
        pair<int, int> start;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start = {i, j};
                } else if (classroom[i][j] == 'L') {
                    litterPositions.push_back({i, j});
                }
            }
        }

        int litterCount = litterPositions.size();
        vector<vector<int>> dist(litterCount + 1, vector<int>(litterCount + 1, -1));
        auto bfs = [&](pair<int, int> src, int idx) {
            vector<vector<int>> visited(m, vector<int>(n, -1));
            queue<tuple<int, int, int>> q;
            q.push({src.first, src.second, energy});
            visited[src.first][src.second] = 0;

            while (!q.empty()) {
                auto [x, y, e] = q.front();
                q.pop();

                for (auto [dx, dy] : vector<pair<int, int>>{{0,1},{1,0},{0,-1},{-1,0}}) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                        int ne = e - 1;
                        if (classroom[nx][ny] == 'R') {
                            ne = energy;
                        }
                        if (ne >= 0 && (visited[nx][ny] == -1 || visited[nx][ny] < ne)) {
                            visited[nx][ny] = ne;
                            q.push({nx, ny, ne});
                        }
                    }
                }
            }

            for (int i = 0; i < litterCount; ++i) {
                auto [lx, ly] = litterPositions[i];
                if (visited[lx][ly] != -1) {
                    dist[idx][i] = visited[lx][ly];
                }
            }
        };

        bfs(start, litterCount);
        for (int i = 0          
    }
};
