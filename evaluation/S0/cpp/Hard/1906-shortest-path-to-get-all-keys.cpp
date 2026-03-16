// Source: https://leetcode.com/problems/shortest-path-to-get-all-keys/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n grid grid where:
//
//
// 	'.' is an empty cell.
// 	'#' is a wall.
// 	'@' is the starting point.
// 	Lowercase letters represent keys.
// 	Uppercase letters represent locks.
//
//
// You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.
//
// If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.
//
// For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
//
// Return the lowest number of moves to acquire all keys. If it is impossible, return -1.
//
// Example:
// Input: grid = ["@.a..","###.#","b.A.B"]
// Output: 8
// Explanation: Note that the goal is to obtain all the keys not to open all the locks.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 30
// 	grid[i][j] is either an English letter, '.', '#', or '@'. 
// 	There is exactly one '@' in the grid.
// 	The number of keys in the grid is in the range [1, 6].
// 	Each key in the grid is unique.
// 	Each key in the grid has a matching lock.
//

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int totalKeys = 0;
        int startX, startY;
        
        // Find starting point and total keys
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    startX = i;
                    startY = j;
                } else if (islower(grid[i][j])) {
                    totalKeys |= (1 << (grid[i][j] - 'a'));
                }
            }
        }
        
        // BFS
        queue<tuple<int, int, int, int>> q; // x, y, keys, steps
        set<tuple<int, int, int>> visited; // x, y, keys
        q.push({startX, startY, 0, 0});
        visited.insert({startX, startY, 0});
        
        vector<int> directions = {0, 1, 0, -1, 0};
        
        while (!q.empty()) {
            auto [x, y, keys, steps] = q.front();
            q.pop();
            
            // Check if all keys are collected
            if (keys == totalKeys) {
                return steps;
            }
            
            // Explore neighbors
            for (int d = 0; d < 4; d++) {
                int newX = x + directions[d];
                int newY = y + directions[d + 1];
                int newKeys = keys;
                
                // Check bounds
                if (newX < 0 || newX >= m || newY < 0 || newY >= n) continue;
                
                char cell = grid[newX][newY];
                
                // Wall
                if (cell == '#') continue;
                
                // Key
                if (islower(cell)) {
                    newKeys |= (1 << (cell - 'a'));
                }
                
                // Lock
                if (isupper(cell) && !(keys & (1 << (cell - 'A')))) {
                    continue; // don't have the key for this lock
                }
                
                // Check if visited
                if (visited.count({newX, newY, newKeys}) == 0) {
                    visited.insert({newX, newY, newKeys});
                    q.push({newX, newY, newKeys, steps + 1});
                }   
                
            }
        }
        
        return -1;
    }
};
