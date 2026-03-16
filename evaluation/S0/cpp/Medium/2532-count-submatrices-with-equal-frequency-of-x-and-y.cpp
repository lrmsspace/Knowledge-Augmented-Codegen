// Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:
//
//
// 	grid[0][0]
// 	an equal frequency of 'X' and 'Y'.
// 	at least one 'X'.
//
// Example:
// Input: grid = [["X","Y","."],["Y",".","."]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 1000
// 	grid[i][j] is either 'X', 'Y', or '.'.
//

class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int result = 0;

        for (int top = 0; top < rows; ++top) {
            vector<int> countX(cols, 0);
            vector<int> countY(cols, 0);

            for (int bottom = top; bottom < rows; ++bottom) {
                for (int col = 0; col < cols; ++col) {
                    if (grid[bottom][col] == 'X') {
                        countX[col]++;
                    } else if (grid[bottom][col] == 'Y') {
                        countY[col]++;
                    }
                }

                unordered_map<int, int> freqMap;
                freqMap[0] = 1;
                int currDiff = 0;
                int currXCount = 0;

                for (int col = 0; col < cols; ++col) {
                    currDiff += countX[col] - countY[col];
                    currXCount += countX[col];

                    if (currXCount > 0) {
                        result += freqMap[currDiff];
                    }

                    freqMap[currDiff]++;
                }
            }
        }

        return result;          
    }
};
