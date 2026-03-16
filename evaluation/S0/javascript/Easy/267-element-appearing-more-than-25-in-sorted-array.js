// Source: https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.
//
// Example:
// Input: arr = [1,2,2,6,6,6,6,7,10]
// Output: 6
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 105
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var findSpecialInteger = function(arr) {
    const n = arr.length;
    let count = 1;
    for (let i = 1; i < n; i++) {
        if (arr[i] === arr[i - 1]) {
            count++;
        } else {
            count = 1;
        }
        if (count > n / 4) {
            return arr[i];
        }
    }
    return arr[0];
};