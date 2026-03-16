// Source: https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
//
// A V-shaped diagonal segment is defined as:
//
//
// 	The segment starts with 1.
// 	The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
// 	The segment:
// 	
// 		Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left, top-right to bottom-left, or bottom-left to top-right).
// 		Continues the sequence in the same diagonal direction.
// 		Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining the sequence.
// 	
// 	
//
//
// Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
//
// Example:
// Input: grid = [[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]]
//
// Output: 5
//
// Explanation:
//
//
//
// The longest V-shaped diagonal segment has a length of 5 and follows these coordinates: (0,2) → (1,3) → (2,4), takes a 90-degree clockwise turn at (2,4), and continues as (3,3) → (4,2).
//
// Constraints:
// n == grid.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	grid[i][j] is either 0, 1 or 2.
//

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int maxLen = 0;

        // Directions: top-left, top-right, bottom-left, bottom-right
        vector<pair<int, int>> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    // Try all starting directions
                    for (auto& dir : directions) {
                        int len = 1;
                        int x = i + dir.first;
                        int y = j + dir.second;
                        int expected = 2;

                        // Move in the initial direction
                        while (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == expected) {
                            len++;
                            expected = (expected == 2) ? 0 : 2;
                            x += dir.first;
                            y += dir.second;
                        }

                        maxLen = max(maxLen, len);

                        // Try turning clockwise
                        pair<int, int> turnDir = {dir.second, -dir.first};
                        x -= dir.first; // step back to last valid position
                        y -= dir.second;

                        expected = (expected == 2) ? 0 : 2;

                        x += turnDir.first;
                        y += turnDir.second;

                        while (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == expected) {
                            len++;
                            expected = (expected == 2) ? 0 : 2;
                            x += turnDir.first;
                            y += turnDir.second;
                        }

                        maxLen = max(maxLen, len);
                    }
                }
            }
        }

        return maxLen;          
    }
};
