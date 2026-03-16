// Source: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
//
// Note that the subarray needs to be non-empty after deleting one element.
//
// Example:
// Input: arr = [1,-2,0,3]
// Output: 4
// Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
//
// Constraints:
// 1 <= arr.length <= 105
// 	-104 <= arr[i] <= 104
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var maximumSum = function(arr) {
    const n = arr.length;
    let maxSumNoDeletion = arr[0];
    let maxSumOneDeletion = 0;
    let result = arr[0];
    for (let i = 1; i < n; i++) {
        maxSumOneDeletion = Math.max(maxSumOneDeletion + arr[i], maxSumNoDeletion);
        maxSumNoDeletion = Math.max(maxSumNoDeletion + arr[i], arr[i]);
        result = Math.max(result, Math.max(maxSumNoDeletion, maxSumOneDeletion));
    }
    return result;
        
    
};
