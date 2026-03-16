// Source: https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.
//
// It is guaranteed that there will be a rectangle with a sum no larger than k.
//
// Example:
// Input: matrix = [[1,0,1],[0,-2,3]], k = 2
// Output: 2
// Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 100
// 	-100 <= matrix[i][j] <= 100
// 	-105 <= k <= 105
//
//
//  
// Follow up: What if the number of rows is much larger than the number of columns?
//

class Solution {
    public int maxSumSubmatrix(int[][] matrix, int k) {
        int rows = matrix.length, cols = matrix[0].length;
        int maxSum = Integer.MIN_VALUE;

        for (int left = 0; left < cols; left++) {
            int[] rowSums = new int[rows];

            for (int right = left; right < cols; right++) {
                for (int r = 0; r < rows; r++) {
                    rowSums[r] += matrix[r][right];
                }

                maxSum = Math.max(maxSum, getMaxSubarrayNoLargerThanK(rowSums, k));
                if (maxSum == k) return k; // Early exit if we found the best possible sum
            }
        }

        return maxSum;          
    }
}
