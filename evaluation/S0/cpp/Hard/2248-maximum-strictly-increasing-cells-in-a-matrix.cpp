// Source: https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.
//
// From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.
//
// Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.
//
// Return an integer denoting the maximum number of cells that can be visited.
//
// Example:
// Input: mat = [[3,1],[3,4]]
// Output: 2
// Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2.
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	-105 <= mat[i][j] <= 105
//

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        
        vector<tuple<int, int, int>> cells; // (value, row, col)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells.emplace_back(mat[i][j], i, j);
            }
        }
        
        sort(cells.begin(), cells.end());
        
        vector<int> rowMax(m, 0);
        vector<int> colMax(n, 0);
        vector<int> dp(m * n, 0);
        
        int i = 0;
        while (i < cells.size()) {
            int j = i;
            vector<pair<int, int>> updates; // (index in dp, new value)
            
            while (j < cells.size() && get<0>(cells[j]) == get<0>(cells[i])) {
                int r = get<1>(cells[j]);
                int c = get<2>(cells[j]);
                int idx = r * n + c;
                
                dp[idx] = max(rowMax[r], colMax[c]) + 1;
                updates.emplace_back(idx, dp[idx]);
                
                j++;
            }
            
            for (const auto& [idx, val] : updates) {
                int r = idx / n;
                int c = idx % n;
                rowMax[r] = max(rowMax[r], val);
                colMax[c] = max(colMax[c], val);
            }
            
            i = j;
        }
        
        return *max_element(dp.begin(), dp.end());          
    }
};
