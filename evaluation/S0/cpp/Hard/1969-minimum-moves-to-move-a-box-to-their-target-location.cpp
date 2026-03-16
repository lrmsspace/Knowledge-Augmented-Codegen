// Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
//
// Problem Description:
// A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
//
// The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
//
// Your task is to move the box 'B' to the target position 'T' under the following rules:
//
//
// 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
// 	The character '.' represents the floor which means a free cell to walk.
// 	The character '#' represents the wall which means an obstacle (impossible to walk there).
// 	There is only one box 'B' and one target cell 'T' in the grid.
// 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
// 	The player cannot walk through the box.
//
//
// Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [["#","#","#","#","#","#"],
//                ["#","T","#","#","#","#"],
//                ["#",".",".","B",".","#"],
//                ["#",".","#","#",".","#"],
//                ["#",".",".",".","S","#"],
//                ["#","#","#","#","#","#"]]
// Output: 3
// Explanation: We return only the number of times the box is pushed.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
// 	There is only one character 'S', 'B', and 'T' in the grid.
//

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        pair<int, int> box, target, player;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'B') box = {i, j};
                else if (grid[i][j] == 'T') target = {i, j};
                else if (grid[i][j] == 'S') player = {i, j};
            }
        }
        
        queue<tuple<int, int, int, int, int>> q;
        q.push({box.first, box.second, player.first, player.second, 0});
        
        set<tuple<int, int, int, int>> visited;
        visited.insert({box.first, box.second, player.first, player.second});
        
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        while (!q.empty()) {
            auto [bx, by, px, py, pushes] = q.front();
            q.pop();
            
            if (bx == target.first && by == target.second) {
                return pushes;
            }
            
            for (auto& dir : directions) {
                int nbx = bx + dir.first;
                int nby = by + dir.second;
                int opx = bx - dir.first;
                int opy = by - dir.second;
                
                if (nbx < 0 || nbx >= m || nby < 0 || nby >= n || grid[nbx][nby] == '#') continue;
                if (opx < 0 || opx >= m || opy < 0 || opy >= n || grid[opx][opy] == '#') continue;
                
                // Check if player can reach the opposite side of the box
                vector<vector<bool>> canReach(m, vector<bool>(n, false));
                queue<pair<int, int>> pq;
                pq.push({px, py});
                canReach[px][py] = true;
                
                while (!pq.empty()) {
                    auto [cx, cy] = pq.front();
                    pq.pop();
                    
                    for (auto& d : directions) {
                        int nx = cx + d.first;
                        int ny = cy + d.second;
                        
                        if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                        if (canReach[nx][ny]) continue;
                        if (grid[nx][ny] == '#') continue;
                        if (nx == bx && ny == by) continue; // Can't go through the box
                        
                        canReach[nx][ny] = true;
                        pq.push({nx, ny});
                    }
                }
                if (canReach[opx][opy]) {
                    if (visited.count({nbx, nby, bx, by}) == 0) {
                        visited.insert({nbx, nby, bx, by});
                        q.push({nbx, nby, bx, by, pushes + 1});
                    }
                }
                
            }
        }
        return -1;
    }
};
