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

int maxAbsValExpr(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    int maxVal = 0;
    int expressions[4][2] = {
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };

    for (int k = 0; k < 4; k++) {
        int maxExpr = INT_MIN;
        int minExpr = INT_MAX;

        for (int i = 0; i < arr1Size; i++) {
            int currentExpr = expressions[k][0] * arr1[i] + expressions[k][1] * arr2[i] + i;

            if (currentExpr > maxExpr) {
                maxExpr = currentExpr;
            }
            if (currentExpr < minExpr) {
                minExpr = currentExpr;
            }
        }

        int currentMaxVal = maxExpr - minExpr;
        if (currentMaxVal > maxVal) {
            maxVal = currentMaxVal;
        }
    }

    return maxVal;      
}
