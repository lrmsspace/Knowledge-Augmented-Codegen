// Source: https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays of equal length target and arr. In one step, you can select any non-empty subarray of arr and reverse it. You are allowed to make any number of steps.
//
// Return true if you can make arr equal to target or false otherwise.
//
// Example:
// Input: target = [1,2,3,4], arr = [2,4,1,3]
// Output: true
// Explanation: You can follow the next steps to convert arr to target:
// 1- Reverse subarray [2,4,1], arr becomes [1,4,2,3]
// 2- Reverse subarray [4,2], arr becomes [1,2,4,3]
// 3- Reverse subarray [4,3], arr becomes [1,2,3,4]
// There are multiple ways to convert arr to target, this is not the only way to do so.
//
// Constraints:
// target.length == arr.length
// 	1 <= target.length <= 1000
// 	1 <= target[i] <= 1000
// 	1 <= arr[i] <= 1000
//

/**
 * @param {number[]} target
 * @param {number[]} arr
 * @return {boolean}
 */
var canBeEqual = function(target, arr) {
    const countMap = new Map();
    for (const num of target) {
        countMap.set(num, (countMap.get(num) || 0) + 1);
    }
    for (const num of arr) {
        if (!countMap.has(num)) {
            return false;
        }
        countMap.set(num, countMap.get(num) - 1);
        if (countMap.get(num) === 0) {
            countMap.delete(num);
        }
    }
    return countMap.size === 0;
};