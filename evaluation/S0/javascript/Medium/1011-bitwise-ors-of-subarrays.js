// Source: https://leetcode.com/problems/bitwise-ors-of-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty subarrays of arr.
//
// The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of a subarray of one integer is that integer.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: arr = [0]
// Output: 1
// Explanation: There is only one possible result: 0.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	0 <= arr[i] <= 109
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var subarrayBitwiseORs = function(arr) {
    const res = new Set();
    let cur = new Set();
    for (const num of arr) {
        const next = new Set([num]);
        for (const prev of cur) {
            next.add(prev | num);
        }
        for (const val of next) {
            res.add(val);
        }
        cur = next;
    }
    return res.size;
};
