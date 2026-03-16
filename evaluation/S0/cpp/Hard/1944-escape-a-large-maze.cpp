// Source: https://leetcode.com/problems/escape-a-large-maze/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).
//
// We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).
//
// Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.
//
// Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.
//
// Example:
// Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
// Output: false
// Explanation: The target square is inaccessible starting from the source square because we cannot move.
// We cannot move north or east because those squares are blocked.
// We cannot move south or west because we cannot go outside of the grid.
//
// Constraints:
// 0 <= blocked.length <= 200
// 	blocked[i].length == 2
// 	0 <= xi, yi < 106
// 	source.length == target.length == 2
// 	0 <= sx, sy, tx, ty < 106
// 	source != target
// 	It is guaranteed that source and target are not blocked.
//

class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        const int N = 1e6;
        const int MAX_STEPS = 20000; // A limit to prevent infinite search

        unordered_set<long long> blockedSet;
        for (const auto& b : blocked) {
            blockedSet.insert(((long long)b[0] << 20) | b[1]);
        }

        auto bfs = [&](const vector<int>& start, const vector<int>& end) {
            queue<vector<int>> q;
            q.push(start);
            unordered_set<long long> visited;
            visited.insert(((long long)start[0] << 20) | start[1]);
            int steps = 0;

            vector<vector<int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

            while (!q.empty() && steps < MAX_STEPS) {
                auto curr = q.front(); q.pop();
                if (curr == end) return true;

                for (const auto& dir : directions) {
                    int nx = curr[0] + dir[0];
                    int ny = curr[1] + dir[1];
                    long long code = ((long long)nx << 20) | ny;

                    if (nx >= 0 && nx < N && ny >= 0 && ny < N &&
                        blockedSet.find(code) == blockedSet.end() &&
                        visited.find(code) == visited.end()) {
                        visited.insert(code);
                        q.push({nx, ny});
                    }
                }
                steps++;
            }
            return steps >= MAX_STEPS; // If we reached max steps, we are not enclosed
        };

        return bfs(source, target) && bfs(target, source);          
    }
};
