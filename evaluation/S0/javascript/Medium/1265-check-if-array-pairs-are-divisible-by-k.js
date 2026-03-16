// Source: https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr of even length n and an integer k.
//
// We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
//
// Return true If you can find a way to do that or false otherwise.
//
// Example:
// Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
// Output: true
// Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
//
// Constraints:
// arr.length == n
// 	1 <= n <= 105
// 	n is even.
// 	-109 <= arr[i] <= 109
// 	1 <= k <= 105
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {boolean}
 */
var canArrange = function(arr, k) {
    const remainderCount = new Map();
    for (let num of arr) {
        let remainder = ((num % k) + k) % k; // Handle negative numbers
        remainderCount.set(remainder, (remainderCount.get(remainder) || 0) + 1);
    }
    for (let [remainder, count] of remainderCount.entries()) {
        if (remainder === 0) {
            if (count % 2 !== 0) return false;
        } else {
            if (count !== remainderCount.get(k - remainder)) return false;
        }
    }
    return true;
};