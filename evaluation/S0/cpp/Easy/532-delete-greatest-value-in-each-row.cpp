// Source: https://leetcode.com/problems/delete-greatest-value-in-each-row/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n matrix grid consisting of positive integers.
//
// Perform the following operation until grid becomes empty:
//
//
// 	Delete the element with the greatest value from each row. If multiple such elements exist, delete any of them.
// 	Add the maximum of deleted elements to the answer.
//
//
// Note that the number of columns decreases by one after each operation.
//
// Return the answer after performing the operations described above.
//
// Example:
// Input: grid = [[1,2,4],[3,3,1]]
// Output: 8
// Explanation: The diagram above shows the removed values in each step.
// - In the first operation, we remove 4 from the first row and 3 from the second row (notice that, there are two cells with value 3 and we can remove any of them). We add 4 to the answer.
// - In the second operation, we remove 2 from the first row and 3 from the second row. We add 3 to the answer.
// - In the third operation, we remove 1 from the first row and 1 from the second row. We add 1 to the answer.
// The final answer = 4 + 3 + 1 = 8.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 100
//

class Solution {
public:
    int deleteGreatestValue(vector<vector<int>>& grid) {
        int result = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        // Sort each row to facilitate easy access to the largest elements
        for (int i = 0; i < rows; ++i) {
            sort(grid[i].begin(), grid[i].end());
        }

        // Iterate over each column from the last to the first
        for (int col = cols - 1; col >= 0; --col) {
            int maxInColumn = 0;

            // Find the maximum element in the current column across all rows
            for (int row = 0; row < rows; ++row) {
                maxInColumn = max(maxInColumn, grid[row][col]);
            }

            // Add the maximum found in this column to the result
            result += maxInColumn;
        }

        return result;          
    }
};
