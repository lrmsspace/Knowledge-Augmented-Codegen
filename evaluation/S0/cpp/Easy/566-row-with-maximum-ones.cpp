// Source: https://leetcode.com/problems/row-with-maximum-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a m x n binary matrix mat, find the 0-indexed position of the row that contains the maximum count of ones, and the number of ones in that row.
//
// In case there are multiple rows that have the maximum count of ones, the row with the smallest row number should be selected.
//
// Return an array containing the index of the row, and the number of ones in it.
//
// Example:
// Input: mat = [[0,1],[1,0]]
// Output: [0,1]
// Explanation: Both rows have the same number of 1's. So we return the index of the smaller row, 0, and the maximum count of ones (1). So, the answer is [0,1].
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 100 
// 	mat[i][j] is either 0 or 1.
//

class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        int maxOnes = -1;
        int rowIndex = -1;
        int m = mat.size();
        int n = mat[0].size();

        for (int i = 0; i < m; ++i) {
            int countOnes = 0;
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) {
                    countOnes++;
                }
            }
            if (countOnes > maxOnes) {
                maxOnes = countOnes;
                rowIndex = i;
            }
        }

        return {rowIndex, maxOnes};         
    }
};
