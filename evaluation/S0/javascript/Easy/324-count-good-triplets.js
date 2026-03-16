// Source: https://leetcode.com/problems/count-good-triplets/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, and three integers a, b and c. You need to find the number of good triplets.
//
// A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:
//
//
// 	0 <= i < j < k < arr.length
// 	|arr[i] - arr[j]| <= a
// 	|arr[j] - arr[k]| <= b
// 	|arr[i] - arr[k]| <= c
//
//
// Where |x| denotes the absolute value of x.
//
// Return the number of good triplets.
//
// Example:
// Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
// Output: 4
// Explanation: There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1), (0,1,1)].
//
// Constraints:
// 3 <= arr.length <= 100
// 	0 <= arr[i] <= 1000
// 	0 <= a, b, c <= 1000
//

/**
 * @param {number[]} arr
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @return {number}
 */
var countGoodTriplets = function(arr, a, b, c) {
    let count = 0;
    const n = arr.length;
    for (let i = 0; i < n - 2; i++) {
        for (let j = i + 1; j < n - 1; j++) {
            for (let k = j + 1; k < n; k++) {
                if (Math.abs(arr[i] - arr[j]) <= a &&
                    Math.abs(arr[j] - arr[k]) <= b &&
                    Math.abs(arr[i] - arr[k]) <= c) {
                    count++;
                }
            }
        }
    }
    return count;
};