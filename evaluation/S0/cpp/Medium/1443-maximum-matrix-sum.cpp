// Source: https://leetcode.com/problems/maximum-matrix-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n integer matrix. You can do the following operation any number of times:
//
//
// 	Choose any two adjacent elements of matrix and multiply each of them by -1.
//
//
// Two elements are considered adjacent if and only if they share a border.
//
// Your goal is to maximize the summation of the matrix's elements. Return the maximum sum of the matrix's elements using the operation mentioned above.
//
// Example:
// Input: matrix = [[1,-1],[-1,1]]
// Output: 4
// Explanation: We can follow the following steps to reach sum equals 4:
// - Multiply the 2 elements in the first row by -1.
// - Multiply the 2 elements in the first column by -1.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	2 <= n <= 250
// 	-105 <= matrix[i][j] <= 105
//

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long totalSum = 0;
        int minAbsValue = INT_MAX;
        int negativeCount = 0;

        for (const auto& row : matrix) {
            for (int val : row) {
                int absVal = abs(val);
                totalSum += absVal;
                minAbsValue = min(minAbsValue, absVal);
                if (val < 0) {
                    negativeCount++;
                }
            }
        }

        // If there's an odd number of negative numbers, we need to subtract twice the smallest absolute value
        if (negativeCount % 2 != 0) {
            totalSum -= 2 * minAbsValue;
        }

        return totalSum;            
    }
};
