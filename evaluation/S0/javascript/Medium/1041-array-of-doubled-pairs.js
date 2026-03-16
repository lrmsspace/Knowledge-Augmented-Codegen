// Source: https://leetcode.com/problems/array-of-doubled-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array of even length arr, return true if it is possible to reorder arr such that arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2, or false otherwise.
//
// Example:
// Input: arr = [3,1,3,6]
// Output: false
//
// Constraints:
// 2 <= arr.length <= 3 * 104
// 	arr.length is even.
// 	-105 <= arr[i] <= 105
//

/**
 * @param {number[]} arr
 * @return {boolean}
 */
var canReorderDoubled = function(arr) {
    const countMap = new Map();
    for (const num of arr) {
        countMap.set(num, (countMap.get(num) || 0) + 1);
    }   
    const sortedKeys = Array.from(countMap.keys()).sort((a, b) => Math.abs(a) - Math.abs(b));
    for (const key of sortedKeys) {
        if (countMap.get(key) > countMap.get(2 * key) || (key === 0 && countMap.get(key) % 2 !== 0)) {
            return false;
        }  
        countMap.set(2 * key, countMap.get(2 * key) - countMap.get(key));
    }
    return true;
};
