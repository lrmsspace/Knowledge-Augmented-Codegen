// Source: https://leetcode.com/problems/duplicate-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.
//
// Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.
//
// Example:
// Input: arr = [1,0,2,3,0,4,5,0]
// Output: [1,0,0,2,3,0,0,4]
// Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 9
//

/**
 * @param {number[]} arr
 * @return {void} Do not return anything, modify arr in-place instead.
 */
var duplicateZeros = function(arr) {
    const n = arr.length;
    let i = 0;
    let j = 0;
    while (j < n) {
        if (arr[i] === 0) {
            j += 2;
        } else {
            j += 1;
        }
        i += 1;
    }
    i -= 1;
    j -= 1;
    while (i >= 0) {
        if (j < n) {
            arr[j] = arr[i];
        }
        if (arr[i] === 0) {
            j -= 1;
        }
        i -= 1;
        j -= 1;
    }
    
};
