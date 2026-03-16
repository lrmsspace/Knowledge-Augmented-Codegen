// Source: https://leetcode.com/problems/last-day-where-you-can-still-cross/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col representing the number of rows and columns in the matrix, respectively.
//
// Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) will be covered with water (i.e., changed to 1).
//
// You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal directions (left, right, up, and down).
//
// Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.
//
// Example:
// Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
// Output: 2
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 2.
//
// Constraints:
// 2 <= row, col <= 2 * 104
// 	4 <= row * col <= 2 * 104
// 	cells.length == row * col
// 	1 <= ri <= row
// 	1 <= ci <= col
// 	All the values of cells are unique.
//

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int left = 1, right = row * col;
        int result = 0;
        
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Create grid for day 'mid'
            vector<vector<int>> grid(row, vector<int>(col, 0));
            for (int i = 0; i < mid; i++) {
                grid[cells[i][0] - 1][cells[i][1] - 1] = 1; // flooded
            }
            
            // BFS from top row to bottom row
            queue<pair<int, int>> q;
            vector<vector<bool>> visited(row, vector<bool>(col, false));
            
            for (int c = 0; c < col; c++) {
                if (grid[0][c] == 0) {
                    q.push({0, c});
                    visited[0][c] = true;
                }
            }
            
            bool canCross = false;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                
                if (r == row - 1) {
                    canCross = true;
                    break;
                }
                
                for (auto& dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < row && nc >= 0 && nc < col &&
                        grid[nr][nc] == 0 && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
            
            if (canCross) {
                result = mid; // update result
                left = mid + 1; // try for a later day
            } else {
                right = mid - 1; // try for an earlier day
            }
        }
        
        return result;          
    }
};
