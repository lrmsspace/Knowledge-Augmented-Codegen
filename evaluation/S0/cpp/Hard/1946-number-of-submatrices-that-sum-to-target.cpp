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
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int result = 0;
        
        // Prefix sum for each row
        for (int r = 0; r < rows; r++) {
            for (int c = 1; c < cols; c++) {
                matrix[r][c] += matrix[r][c - 1];
            }
        }
        
        // Fix left and right column boundaries
        for (int left = 0; left < cols; left++) {
            for (int right = left; right < cols; right++) {
                unordered_map<int, int> prefixSumCount;
                prefixSumCount[0] = 1;
                int currSum = 0;
                
                // Calculate sums for rows between left and right
                for (int r = 0; r < rows; r++) {
                    int rowSum = matrix[r][right];
                    if (left > 0) {
                        rowSum -= matrix[r][left - 1];
                    }
                    currSum += rowSum;
                    
                    if (prefixSumCount.find(currSum - target) != prefixSumCount.end()) {
                        result += prefixSumCount[currSum - target];
                    }
                    
                    prefixSumCount[currSum]++;
                }
            }
        }
        
        return result;          
    }
};
