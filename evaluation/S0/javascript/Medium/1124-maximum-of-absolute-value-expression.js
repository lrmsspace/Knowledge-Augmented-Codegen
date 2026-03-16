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

/**
 * @param {number[]} arr1
 * @param {number[]} arr2
 * @return {number}
 */
var maxAbsValExpr = function(arr1, arr2) {
    const n = arr1.length;
    let result = 0;
    const signs = [[1, 1], [1, -1], [-1, 1], [-1, -1]];
    for (const [s1, s2] of signs) {
        let maxVal = -Infinity;
        for (let i = 0; i < n; i++) {
            const current = s1 * arr1[i] + s2 * arr2[i] + i;
            result = Math.max(result, current - maxVal);
            maxVal = Math.max(maxVal, current);
        }
    }
    return result;
        
};
