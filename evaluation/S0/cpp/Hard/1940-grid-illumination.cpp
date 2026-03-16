// Source: https://leetcode.com/problems/grid-illumination/   |   Difficulty: Hard
//
// Problem Description:
// There is a 2D grid of size n x n where each cell of this grid has a lamp that is initially turned off.
//
// You are given a 2D array of lamp positions lamps, where lamps[i] = [rowi, coli] indicates that the lamp at grid[rowi][coli] is turned on. Even if the same lamp is listed more than once, it is turned on.
//
// When a lamp is turned on, it illuminates its cell and all other cells in the same row, column, or diagonal.
//
// You are also given another 2D array queries, where queries[j] = [rowj, colj]. For the jth query, determine whether grid[rowj][colj] is illuminated or not. After answering the jth query, turn off the lamp at grid[rowj][colj] and its 8 adjacent lamps if they exist. A lamp is adjacent if its cell shares either a side or corner with grid[rowj][colj].
//
// Return an array of integers ans, where ans[j] should be 1 if the cell in the jth query was illuminated, or 0 if the lamp was not.
//
// Example:
// Input: n = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
// Output: [1,0]
// Explanation: We have the initial grid with all lamps turned off. In the above picture we see the grid after turning on the lamp at grid[0][0] then turning on the lamp at grid[4][4].
// The 0th query asks if the lamp at grid[1][1] is illuminated or not (the blue square). It is illuminated, so set ans[0] = 1. Then, we turn off all lamps in the red square.
//
// The 1st query asks if the lamp at grid[1][0] is illuminated or not (the blue square). It is not illuminated, so set ans[1] = 0. Then, we turn off all lamps in the red rectangle.
//
// Constraints:
// 1 <= n <= 109
// 	0 <= lamps.length <= 20000
// 	0 <= queries.length <= 20000
// 	lamps[i].length == 2
// 	0 <= rowi, coli < n
// 	queries[j].length == 2
// 	0 <= rowj, colj < n
//

class Solution {
public:
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        unordered_map<long long, int> rowCount, colCount, diag1Count, diag2Count;
        unordered_set<long long> lampSet;
        
        auto encode = [](int x, int y) {
            return ((long long)x << 32) | (long long)y;
        };
        
        for (const auto& lamp : lamps) {
            int r = lamp[0], c = lamp[1];
            long long code = encode(r, c);
            if (lampSet.count(code)) continue; // avoid duplicates
            lampSet.insert(code);
            rowCount[r]++;
            colCount[c]++;
            diag1Count[r - c]++;
            diag2Count[r + c]++;
        }
        
        vector<int> result;
        vector<pair<int, int>> directions = {
            {0, 0}, {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},          {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        for (const auto& query : queries) {
            int r = query[0], c = query[1];
            if (rowCount[r] > 0 || colCount[c] > 0 || diag1Count[r - c] > 0 || diag2Count[r + c] > 0) {
                result.push_back(1);
            } else {
                result.push_back(0);
            }
            
            // Turn off lamps in the adjacent cells
            for (const auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;
                long long code = encode(nr, nc);
                if (lampSet.count(code)) {
                    lampSet.erase(code);
                    rowCount[nr]--;
                    colCount[nc]--;
                    diag1Count[nr - nc]--;
                    diag2Count[nr + nc]--;
                }
            }
        }
        
        return result;          
    }
};
