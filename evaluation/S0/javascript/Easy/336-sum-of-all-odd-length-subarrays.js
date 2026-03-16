// Source: https://leetcode.com/problems/sum-of-all-odd-length-subarrays/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers arr, return the sum of all possible odd-length subarrays of arr.
//
// A subarray is a contiguous subsequence of the array.
//
// Example:
// Input: arr = [1,4,2,5,3]
// Output: 58
// Explanation: The odd-length subarrays of arr and their sums are:
// [1] = 1
// [4] = 4
// [2] = 2
// [5] = 5
// [3] = 3
// [1,4,2] = 7
// [4,2,5] = 11
// [2,5,3] = 10
// [1,4,2,5,3] = 15
// If we add all these together we get 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58
//
// Constraints:
// 1 <= arr.length <= 100
// 	1 <= arr[i] <= 1000
//
//
//  
// Follow up:
//
// Could you solve this problem in O(n) time complexity?
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var sumOddLengthSubarrays = function(arr) {
    let totalSum = 0;
    const n = arr.length;
    for (let start = 0; start < n; start++) {
        for (let end = start; end < n; end += 2) { // Increment by 2 to ensure odd length
            for (let k = start; k <= end; k++) {
                totalSum += arr[k];
            }
        }
    }
    return totalSum;    
};
