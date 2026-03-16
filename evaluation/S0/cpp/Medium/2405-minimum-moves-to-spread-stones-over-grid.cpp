// Source: https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing the number of stones in each cell. The grid contains exactly 9 stones, and there can be multiple stones in a single cell.
//
// In one move, you can move a single stone from its current cell to any other cell if the two cells share a side.
//
// Return the minimum number of moves required to place one stone in each cell.
//
// Example:
// Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
// Output: 3
// Explanation: One possible sequence of moves to place one stone in each cell is: 
// 1- Move one stone from cell (2,1) to cell (2,2).
// 2- Move one stone from cell (2,2) to cell (1,2).
// 3- Move one stone from cell (1,2) to cell (0,2).
// In total, it takes 3 moves to place one stone in each cell of the grid.
// It can be shown that 3 is the minimum number of moves required to place one stone in each cell.
//
// Constraints:
// grid.length == grid[i].length == 3
// 	0 <= grid[i][j] <= 9
// 	Sum of grid is equal to 9.
//

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<pair<int, int>> stones;
        vector<pair<int, int>> emptyCells;

        // Collect positions of stones and empty cells
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int count = grid[i][j];
                for (int k = 0; k < count; ++k) {
                    stones.emplace_back(i, j);
                }
                if (count == 0) {
                    emptyCells.emplace_back(i, j);
                }
            }
        }

        int n = stones.size();
        vector<vector<int>> dist(n, vector<int>(n, 0));

        // Calculate Manhattan distances between stones and empty cells
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = abs(stones[i].first - emptyCells[j].first) + abs(stones[i].second - emptyCells[j].second);
            }
        }

        // Hungarian Algorithm to find minimum cost matching
        return hungarianAlgorithm(dist);            
    }
};
