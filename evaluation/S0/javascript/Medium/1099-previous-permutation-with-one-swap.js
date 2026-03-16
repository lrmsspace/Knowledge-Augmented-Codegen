// Source: https://leetcode.com/problems/previous-permutation-with-one-swap/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers arr (not necessarily distinct), return the lexicographically largest permutation that is smaller than arr, that can be made with exactly one swap. If it cannot be done, then return the same array.
//
// Note that a swap exchanges the positions of two numbers arr[i] and arr[j]
//
// Example:
// Input: arr = [3,2,1]
// Output: [3,1,2]
// Explanation: Swapping 2 and 1.
//
// Constraints:
// 1 <= arr.length <= 104
// 	1 <= arr[i] <= 104
//

/**
 * @param {number[]} arr
 * @return {number[]}
 */
var prevPermOpt1 = function(arr) {
    
    const n = arr.length;
    let i = n - 2;
    while (i >= 0 && arr[i] <= arr[i + 1]) {
        i--;
    }
    if (i < 0) return arr;
    let j = n - 1;
    while (arr[j] >= arr[i] || arr[j] === arr[j - 1]) {
        j--;
    }
    [arr[i], arr[j]] = [arr[j], arr[i]];
    return arr;
    
};
