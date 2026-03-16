// Source: https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/   |   Difficulty: Easy
//
// Problem Description:
// An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).
//
// Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.
//
// Example:
// Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
// Output: true
// Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
// Hence, we return true.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	1 <= n <= 100
// 	1 <= matrix[i][j] <= n
//

class Solution {
public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<bool> seen(n + 1, false);

        // Check each row
        for (int i = 0; i < n; ++i) {
            fill(seen.begin(), seen.end(), false);
            for (int j = 0; j < n; ++j) {
                int num = matrix[i][j];
                if (seen[num]) return false;
                seen[num] = true;
            }
        }

        // Check each column
        for (int j = 0; j < n; ++j) {
            fill(seen.begin(), seen.end(), false);
            for (int i = 0; i < n; ++i) {
                int num = matrix[i][j];
                if (seen[num]) return false;
                seen[num] = true;
            }
        }

        return true;            
    }
};
