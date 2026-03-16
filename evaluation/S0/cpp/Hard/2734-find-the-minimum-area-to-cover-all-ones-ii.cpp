// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
//
// Return the minimum possible sum of the area of these rectangles.
//
// Note that the rectangles are allowed to touch.
//
// Example:
// Input: grid = [[1,0,1],[1,1,1]]
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
// 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
// 	The 1 at (1, 1) is covered by a rectangle of area 1.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 30
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there are at least three 1's in grid.
//

class Solution {
public:
    int minimumSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> rows, cols;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
        
        sort(rows.begin(), rows.end());
        sort(cols.begin(), cols.end());
        
        int totalOnes = rows.size();
        int minArea = INT_MAX;
        
        for (int r1 = 0; r1 < totalOnes - 2; r1++) {
            for (int r2 = r1 + 1; r2 < totalOnes - 1; r2++) {
                for (int c1 = 0; c1 < totalOnes - 2; c1++) {
                    for (int c2 = c1 + 1; c2 < totalOnes - 1; c2++) {
                        int area1 = (rows[r1] - rows[0] + 1) * (cols[c1] - cols[0] + 1);
                        int area2 = (rows[r2] - rows[r1 + 1] + 1) * (cols[c2] - cols[c1 + 1] + 1);
                        int area3 = (rows[totalOnes - 1] - rows[r2 + 1] + 1) * (cols[totalOnes - 1] - cols[c2 + 1] + 1);
                        
                        minArea = min(minArea, area1 + area2 + area3);
                    }
                }
            }
        }
        
        return minArea;         
    }
};
