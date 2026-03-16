// Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid and an array queries of size k.
//
// Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
//
//
// 	If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
// 	Otherwise, you do not get any points, and you end this process.
//
//
// After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
//
// Return the resulting array answer.
//
// Example:
// Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
// Explanation: The diagrams above show which cells we visit to get points for each query.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= grid[i][j], queries[i] <= 106
//

class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int m = grid.size();
        int n = grid[0].size();
        int totalCells = m * n;
        
        // Create cells array
        vector<pair<int, pair<int, int>>> cells; // (value, (row, col))
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells.push_back({grid[i][j], {i, j}});
            }
        }
        
        // Sort cells by value
        sort(cells.begin(), cells.end());
        
        // Prepare queries with original indices
        vector<pair<int, int>> queryWithIndex; // (queryValue, originalIndex)
        for (int i = 0; i < queries.size(); i++) {
            queryWithIndex.push_back({queries[i], i});
        }
        
        // Sort queries by value
        sort(queryWithIndex.begin(), queryWithIndex.end());
        
        // Directions for moving in 4 directions
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        // Union-Find structure
        vector<int> parent(totalCells);
        vector<int> size(totalCells, 1);
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unionSets = [&](int a, int b) {
            int rootA = find(a);
            int rootB = find(b);
            if (rootA != rootB) {
                if (size[rootA] < size[rootB]) {
                    swap(rootA, rootB);
                }
                parent[rootB] = rootA;
                size[rootA] += size[rootB];
            }
        };
        
        // Initialize Union-Find
        for (int i = 0; i < totalCells; i++) {
            parent[i] = i;
        }
        
        vector<bool> visited(totalCells, false);
        vector<int> result(queries.size(), 0);
        
        int cellIndex = 0;
        
        // Process each query
        for (const auto& [queryValue, originalIndex] : queryWithIndex) {
            // Add all cells with value less than queryValue
            while (cellIndex < totalCells && cells[cellIndex].first < queryValue) {
                int r = cells[cellIndex].second.first;
                int c = cells[cellIndex].second.second;
                int cellId = r * n + c;
                visited[cellId] = true;
                
                // Union with adjacent visited cells
                for (const auto& dir : directions) {
                    int nr = r + dir.first;
                    int nc = c + dir.second;
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        int neighborId = nr * n + nc;
                        if (visited[neighborId]) {
                            unionSets(cellId, neighborId);
                        }
                    }
                }
                cellIndex++;
            }
            
            // Get the size of the component containing the top-left cell
            if (visited[0]) {
                int root = find(0);
                result[originalIndex] = size[root];
            } else {
                result[originalIndex] = 0;
            }
        }
        return result;
    }
};
