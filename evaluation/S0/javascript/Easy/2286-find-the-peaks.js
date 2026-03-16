// Source: https://leetcode.com/problems/find-the-peaks/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array mountain. Your task is to find all the peaks in the mountain array.
//
// Return an array that consists of indices of peaks in the given array in any order.
//
// Example:
// Input: mountain = [2,4,4]
// Output: []
// Explanation: mountain[0] and mountain[2] can not be a peak because they are first and last elements of the array.
// mountain[1] also can not be a peak because it is not strictly greater than mountain[2].
// So the answer is [].
//
// Constraints:
// 3 <= mountain.length <= 100
// 	1 <= mountain[i] <= 100
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} mountain
 * @return {number[]}
 */
var findPeaks = function(mountain) {
    const peaks = [];
    for (let i = 1; i < mountain.length - 1; i++) {
        if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
            peaks.push(i);
        }
    }
    return peaks;   
};
