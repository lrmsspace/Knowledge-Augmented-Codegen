// Source: https://leetcode.com/problems/minimum-absolute-difference/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of any two elements.
//
// Return a list of pairs in ascending order(with respect to pairs), each pair [a, b] follows
//
//
// 	a, b are from arr
// 	a < b
// 	b - a equals to the minimum absolute difference of any two elements in arr
//
// Example:
// Input: arr = [4,2,1,3]
// Output: [[1,2],[2,3],[3,4]]
// Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
//
// Constraints:
// 2 <= arr.length <= 105
// 	-106 <= arr[i] <= 106
//

/**
 * @param {number[]} arr
 * @return {number[][]}
 */
var minimumAbsDifference = function(arr) {
    arr.sort((a, b) => a - b);
    let minDiff = Infinity;
    const result = [];
    for (let i = 1; i < arr.length; i++) {
        const diff = arr[i] - arr[i - 1];
        if (diff < minDiff) {
            minDiff = diff;
            result.length = 0; // Clear the result array
            result.push([arr[i - 1], arr[i]]);
        } else if (diff === minDiff) {
            result.push([arr[i - 1], arr[i]]);
        }
    }
    return result;
};