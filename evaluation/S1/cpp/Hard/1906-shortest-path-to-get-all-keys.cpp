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
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int totalKeys = 0;
        int startX, startY;

        // Directions for moving up, down, left, right
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Find starting point and total keys
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '@') {
                    startX = i;
                    startY = j;
                } else if (islower(grid[i][j])) {
                    totalKeys = max(totalKeys, grid[i][j] - 'a' + 1);
                }
            }
        }

        int finalState = (1 << totalKeys) - 1;
        queue<tuple<int, int, int>> q; // (x, y, keys)
        q.push({startX, startY, 0});
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(1 << totalKeys, false)));
        visited[startX][startY][0] = true;
        int steps = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [x, y, keys] = q.front();
                q.pop();

                // Check if all keys are collected
                if (keys == finalState) {
                    return steps;
                }

                for (auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    int nkeys = keys;

                    // Check boundaries
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == '#') {
                        continue;
                    }

                    char cell = grid[nx][ny];

                    // If it's a key, collect it
                    if (islower(cell)) {
                        nkeys |= (1 << (cell - 'a'));
                    }

                    // If it's a lock, check if we have the key
                    if (isupper(cell) && !(nkeys & (1 << (cell - 'A')))) {
                        continue;
                    }
                    if (!visited[nx][ny][nkeys]) {
                        visited[nx][ny][nkeys] = true;
                        q.push({nx, ny, nkeys});
                    }
                }
            }
            steps++;
        }
        return -1; // If it's not possible to collect all keys
    }
};
