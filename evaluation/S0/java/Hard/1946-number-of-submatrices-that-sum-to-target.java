// Source: https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/   |   Difficulty: Hard
//
// Problem Description:
// Given a matrix and a target, return the number of non-empty submatrices that sum to target.
//
// A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
//
// Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.
//
// Example:
// Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
// Output: 4
// Explanation: The four 1x1 submatrices that only contain 0.
//
// Constraints:
// 1 <= matrix.length <= 100
// 	1 <= matrix[0].length <= 100
// 	-1000 <= matrix[i][j] <= 1000
// 	-10^8 <= target <= 10^8
//

class Solution {
    public int numSubmatrixSumTarget(int[][] matrix, int target) {
        int rows = matrix.length;
        int cols = matrix[0].length;

        // Step 1: Compute prefix sums for each row
        for (int r = 0; r < rows; r++) {
            for (int c = 1; c < cols; c++) {
                matrix[r][c] += matrix[r][c - 1];
            }
        }

        int count = 0;

        // Step 2: Iterate over all pairs of columns
        for (int startCol = 0; startCol < cols; startCol++) {
            for (int endCol = startCol; endCol < cols; endCol++) {

                // Map to store the frequency of prefix sums
                Map<Integer, Integer> prefixSumCount = new HashMap<>();
                prefixSumCount.put(0, 1); // Base case: one way to have sum 0
                int currentSum = 0;

                // Step 3: Calculate the sum of submatrices between the two columns
                for (int r = 0; r < rows; r++) {
                    // Calculate the sum of the current row between startCol and endCol
                    int rowSum = matrix[r][endCol] - (startCol > 0 ? matrix[r][startCol - 1] : 0);
                    currentSum += rowSum;

                    // Check if there is a prefix sum that when subtracted from currentSum gives target
                    if (prefixSumCount.containsKey(currentSum - target)) {
                        count += prefixSumCount.get(currentSum - target);
                    }

                    // Update the frequency of the current prefix sum
                    prefixSumCount.put(currentSum, prefixSumCount.getOrDefault(currentSum, 0) + 1);
                }
            }
        }

        return count;                   
    }
}
