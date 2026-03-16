// Source: https://leetcode.com/problems/right-triangles/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D boolean matrix grid.
//
// A collection of 3 elements of grid is a right triangle if one of its elements is in the same row with another element and in the same column with the third element. The 3 elements may not be next to each other.
//
// Return an integer that is the number of right triangles that can be made with 3 elements of grid such that all of them have a value of 1.
//
// Example:
// 0
// 			1
// 			0
// 		
// 		
// 			0
// 			1
// 			1
// 		
// 		
// 			0
// 			1
// 			0
// 		
// 	
//
//
//
// 	
// 		
// 			0
// 			1
// 			0
// 		
// 		
// 			0
// 			1
// 			1
// 		
// 		
// 			0
// 			1
// 			0
// 		
// 	
//
//
//
// 	
// 		
// 			0
// 			1
// 			0
// 		
// 		
// 			0
// 			1
// 			1
// 		
// 		
// 			0
// 			1
// 			0
// 		
// 	
//
//
//
//
// Input: grid = [[0,1,0],[0,1,1],[0,1,0]]
//
// Output: 2
//
// Explanation:
//
// There are two right triangles with elements of the value 1. Notice that the blue ones do not form a right triangle because the 3 elements are in the same column.
//
// Constraints:
// 1 <= grid.length <= 1000
// 	1 <= grid[i].length <= 1000
// 	0 <= grid[i][j] <= 1
//

class Solution {
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<long long> rowCount(rows, 0);
        vector<long long> colCount(cols, 0);

        // Count number of 1's in each row and column
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    rowCount[r]++;
                    colCount[c]++;
                }
            }
        }

        long long totalTriangles = 0;

        // Calculate the number of right triangles
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    totalTriangles += (rowCount[r] - 1) * (colCount[c] - 1);
                }
            }
        }

        return totalTriangles;          
    }
};
