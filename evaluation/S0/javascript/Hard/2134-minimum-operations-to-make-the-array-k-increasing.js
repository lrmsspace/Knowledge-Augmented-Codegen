// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array arr consisting of n positive integers, and a positive integer k.
//
// The array arr is called K-increasing if arr[i-k] <= arr[i] holds for every index i, where k <= i <= n-1.
//
//
// 	For example, arr = [4, 1, 5, 2, 6, 2] is K-increasing for k = 2 because:
//
// 	
// 		arr[0] <= arr[2] (4 <= 5)
// 		arr[1] <= arr[3] (1 <= 2)
// 		arr[2] <= arr[4] (5 <= 6)
// 		arr[3] <= arr[5] (2 <= 2)
// 	
// 	
// 	However, the same arr is not K-increasing for k = 1 (because arr[0] > arr[1]) or k = 3 (because arr[0] > arr[3]).
//
//
// In one operation, you can choose an index i and change arr[i] into any positive integer.
//
// Return the minimum number of operations required to make the array K-increasing for the given k.
//
// Example:
// Input: arr = [5,4,3,2,1], k = 1
// Output: 4
// Explanation:
// For k = 1, the resultant array has to be non-decreasing.
// Some of the K-increasing arrays that can be formed are [5,6,7,8,9], [1,1,1,1,1], [2,2,3,4,4]. All of them require 4 operations.
// It is suboptimal to change the array to, for example, [6,7,8,9,10] because it would take 5 operations.
// It can be shown that we cannot make the array K-increasing in less than 4 operations.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i], k <= arr.length
//

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var kIncreasing = function(arr, k) {
    const n = arr.length;
    let operations = 0;
    for (let start = 0; start < k; start++) {
        const subsequence = [];
        for (let i = start; i < n; i += k) {
            subsequence.push(arr[i]);
        }
        operations += subsequence.length - lengthOfLIS(subsequence);
    }
    return operations;
};
