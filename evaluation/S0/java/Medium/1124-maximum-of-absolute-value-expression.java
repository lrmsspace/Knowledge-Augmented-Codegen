// Source: https://leetcode.com/problems/maximum-of-absolute-value-expression/   |   Difficulty: Medium
//
// Problem Description:
// Given two arrays of integers with equal lengths, return the maximum value of:
//
// |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
//
// where the maximum is taken over all 0 <= i, j < arr1.length.
//
// Example:
// Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
// Output: 13
//
// Constraints:
// 2 <= arr1.length == arr2.length <= 40000
// 	-10^6 <= arr1[i], arr2[i] <= 10^6
//

class Solution {
    public int maxAbsValExpr(int[] arr1, int[] arr2) {
        int n = arr1.length;
        int maxVal = 0;

        // There are 4 combinations of signs for the absolute values
        int[][] signCombinations = {
            {1, 1},
            {1, -1},
            {-1, 1},
            {-1, -1}
        };

        for (int[] signs : signCombinations) {
            int maxExpression = Integer.MIN_VALUE;
            int minExpression = Integer.MAX_VALUE;

            for (int i = 0; i < n; i++) {
                int currentValue = signs[0] * arr1[i] + signs[1] * arr2[i] + i;
                maxExpression = Math.max(maxExpression, currentValue);
                minExpression = Math.min(minExpression, currentValue);
            }

            maxVal = Math.max(maxVal, maxExpression - minExpression);
        }

        return maxVal;          
    }
}
