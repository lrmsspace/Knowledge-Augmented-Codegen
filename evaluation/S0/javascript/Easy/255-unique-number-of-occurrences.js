// Source: https://leetcode.com/problems/unique-number-of-occurrences/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, return true if the number of occurrences of each value in the array is unique or false otherwise.
//
// Example:
// Input: arr = [1,2,2,1,1,3]
// Output: true
// Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	-1000 <= arr[i] <= 1000
//

/**
 * @param {number[]} arr
 * @return {boolean}
 */
var uniqueOccurrences = function(arr) {
    const countMap = new Map();
    for (const num of arr) {
        countMap.set(num, (countMap.get(num) || 0) + 1);
    }
    const occurrences = new Set();
    for (const count of countMap.values()) {
        if (occurrences.has(count)) {
            return false;
        }
        occurrences.add(count);
    }
    return true;
};