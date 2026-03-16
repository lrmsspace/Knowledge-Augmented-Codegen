// Source: https://leetcode.com/problems/bricks-falling-when-hit/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary grid, where each 1 represents a brick and 0 represents an empty space. A brick is stable if:
//
//
// 	It is directly connected to the top of the grid, or
// 	At least one other brick in its four adjacent cells is stable.
//
//
// You are also given an array hits, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location hits[i] = (rowi, coli). The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).
//
// Return an array result, where each result[i] is the number of bricks that will fall after the ith erasure is applied.
//
// Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.
//
// Example:
// Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
// Output: [2]
// Explanation: Starting with the grid:
// [[1,0,0,0],
//  [1,1,1,0]]
// We erase the underlined brick at (1,0), resulting in the grid:
// [[1,0,0,0],
//  [0,1,1,0]]
// The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
// [[1,0,0,0],
//  [0,0,0,0]]
// Hence the result is [2].
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 200
// 	grid[i][j] is 0 or 1.
// 	1 <= hits.length <= 4 * 104
// 	hits[i].length == 2
// 	0 <= xi <= m - 1
// 	0 <= yi <= n - 1
// 	All (xi, yi) are unique.
//

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> copyGrid = grid;
        
        // Apply all hits
        for (const auto& hit : hits) {
            int x = hit[0], y = hit[1];
            if (copyGrid[x][y] == 1) {
                copyGrid[x][y] = 0;
            }
        }
        
        // Union-Find structure
        vector<int> parent(m * n + 1);
        vector<int> size(m * n + 1, 1);
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unionSets = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }
        };
        
        // Initialize Union-Find
        for (int i = 0; i <= m * n; i++) {
            parent[i] = i;
        }
        
        // Connect stable bricks
        for (int j = 0; j < n; j++) {
            if (copyGrid[0][j] == 1) {
                unionSets(j, m * n); // connect to top
            }
        }
        
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (copyGrid[i][j] == 1) {
                    for (const auto& dir : directions) {
                        int ni = i + dir.first;
                        int nj = j + dir.second;
                        if (ni >= 0 && ni < m && nj >= 0 && nj < n && copyGrid[ni][nj] == 1) {
                            unionSets(i * n + j, ni * n + nj);
                        }
                    }
                }
            }
        }
        
        vector<int> result(hits.size(), 0);  
        for (int i = hits.size() - 1; i >= 0; i--) {
            int x = hits[i][0], y = hits[i][1];
            if (grid[x][y] == 0) {
                continue; // No brick to hit
            }
            
            int prevStableSize = size[find(m * n)];
            copyGrid[x][y] = 1; // Restore the brick
            
            // If it's in the top row, connect to top
            if (x == 0) {
                unionSets(y, m * n);
            }
            
            // Connect to adjacent bricks
            for (const auto& dir : directions) {
                int ni = x + dir.first;
                int nj = y + dir.second;
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && copyGrid[ni][nj] == 1) {
                    unionSets(x * n + y, ni * n + nj);
                }
            }
            
            int newStableSize = size[find(m * n)];
            result[i] = max(0, newStableSize - prevStableSize - 1); // Exclude the restored brick
        }
        return result;       
    }
};
