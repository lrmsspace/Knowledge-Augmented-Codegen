// Source: https://leetcode.com/problems/mean-of-array-after-removing-some-elements/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array arr, return the mean of the remaining integers after removing the smallest 5% and the largest 5% of the elements.
//
// Answers within 10-5 of the actual answer will be considered accepted.
//
// Example:
// Input: arr = [1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3]
// Output: 2.00000
// Explanation: After erasing the minimum and the maximum values of this array, all elements are equal to 2, so the mean is 2.
//
// Constraints:
// 20 <= arr.length <= 1000
// 	arr.length is a multiple of 20.
// 	0 <= arr[i] <= 105
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var trimMean = function(arr) {
    arr.sort((a, b) => a - b);
    const n = arr.length;
    const trimCount = n / 20;
    let sum = 0;
    for (let i = trimCount; i < n - trimCount; i++) {
        sum += arr[i];
    }
    return sum / (n - 2 * trimCount);
};
