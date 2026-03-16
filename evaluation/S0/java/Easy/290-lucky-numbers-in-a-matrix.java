// Source: https://leetcode.com/problems/lucky-numbers-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
//
// A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
//
// Example:
// Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
// Output: [15]
// Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= n, m <= 50
// 	1 <= matrix[i][j] <= 105.
// 	All elements in the matrix are distinct.
//

class Solution {
    public List<Integer> luckyNumbers(int[][] matrix) {
        List<Integer> luckyNumbers = new ArrayList<>();

        int rows = matrix.length;
        int cols = matrix[0].length;

        for (int i = 0; i < rows; i++) {
            int minColIndex = 0;

            // Find the index of the minimum element in the current row
            for (int j = 1; j < cols; j++) {
                if (matrix[i][j] < matrix[i][minColIndex]) {
                    minColIndex = j;
                }
            }

            int candidate = matrix[i][minColIndex];
            boolean isLucky = true;

            // Check if the candidate is the maximum in its column
            for (int k = 0; k < rows; k++) {
                if (matrix[k][minColIndex] > candidate) {
                    isLucky = false;
                    break;
                }
            }

            if (isLucky) {
                luckyNumbers.add(candidate);
            }
        }

        return luckyNumbers;            
    }
}
