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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] rowAndMaximumOnes(int[][] mat) {
        int maxRowIndex = -1;
        int maxOnesCount = -1;

        for (int i = 0; i < mat.length; i++) {
            int currentOnesCount = 0;
            for (int j = 0; j < mat[i].length; j++) {
                if (mat[i][j] == 1) {
                    currentOnesCount++;
                }
            }
            if (currentOnesCount > maxOnesCount) {
                maxOnesCount = currentOnesCount;
                maxRowIndex = i;
            }
        }

        return new int[]{maxRowIndex, maxOnesCount};            
    }
}
