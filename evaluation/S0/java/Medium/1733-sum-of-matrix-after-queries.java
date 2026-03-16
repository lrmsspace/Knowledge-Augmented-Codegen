// Source: https://leetcode.com/problems/sum-of-matrix-after-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and a 0-indexed 2D array queries where queries[i] = [typei, indexi, vali].
//
// Initially, there is a 0-indexed n x n matrix filled with 0's. For each query, you must apply one of the following changes:
//
//
// 	if typei == 0, set the values in the row with indexi to vali, overwriting any previous values.
// 	if typei == 1, set the values in the column with indexi to vali, overwriting any previous values.
//
//
// Return the sum of integers in the matrix after all queries are applied.
//
// Example:
// Input: n = 3, queries = [[0,0,1],[1,2,2],[0,2,3],[1,0,4]]
// Output: 23
// Explanation: The image above describes the matrix after each query. The sum of the matrix after all queries are applied is 23.
//
// Constraints:
// 1 <= n <= 104
// 	1 <= queries.length <= 5 * 104
// 	queries[i].length == 3
// 	0 <= typei <= 1
// 	0 <= indexi < n
// 	0 <= vali <= 105
//

class Solution {
    public long matrixSumQueries(int n, int[][] queries) {
        boolean[] rowsUpdated = new boolean[n];
        boolean[] colsUpdated = new boolean[n];
        int rowsCount = 0;
        int colsCount = 0;
        long totalSum = 0;

        for (int i = queries.length - 1; i >= 0; i--) {
            int type = queries[i][0];
            int index = queries[i][1];
            int value = queries[i][2];

            if (type == 0) { // Row update
                if (!rowsUpdated[index]) {
                    totalSum += (long) value * (n - colsCount);
                    rowsUpdated[index] = true;
                    rowsCount++;
                }
            } else { // Column update
                if (!colsUpdated[index]) {
                    totalSum += (long) value * (n - rowsCount);
                    colsUpdated[index] = true;
                    colsCount++;
                }
            }
        }

        return totalSum;            
    }
}
