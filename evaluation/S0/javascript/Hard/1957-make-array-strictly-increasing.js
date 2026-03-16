// Source: https://leetcode.com/problems/make-array-strictly-increasing/   |   Difficulty: Hard
//
// Problem Description:
// Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
//
// In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
//
// If there is no way to make arr1 strictly increasing, return -1.
//
// Example:
// Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
// Output: 1
// Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 2000
// 	0 <= arr1[i], arr2[i] <= 10^9
//

/**
 * @param {number[]} arr1
 * @param {number[]} arr2
 * @return {number}
 */
var makeArrayIncreasing = function(arr1, arr2) {
    const n = arr1.length;
    arr2.sort((a, b) => a - b);
    const dp = new Map();
    dp.set(-1, 0);
    for (const num of arr1) {
        const newDp = new Map();
        for (const [prev, operations] of dp.entries()) {
            if (num > prev) {
                newDp.set(num, Math.min(newDp.get(num) || Infinity, operations));
            }
            const idx = binarySearch(arr2, prev);
            if (idx < arr2.length) {
                newDp.set(arr2[idx], Math.min(newDp.get(arr2[idx]) || Infinity, operations + 1));
            }
        }
        dp.clear();
        for (const [key, value] of newDp.entries()) {
            dp.set(key, value);
        }
    }
    let minOperations = Infinity;
    for (const operations of dp.values()) {
        minOperations = Math.min(minOperations, operations);
    }
    return minOperations === Infinity ? -1 : minOperations;

    
};
