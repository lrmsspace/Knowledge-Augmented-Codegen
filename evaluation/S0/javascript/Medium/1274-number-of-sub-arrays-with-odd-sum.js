// Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr, return the number of subarrays with an odd sum.
//
// Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: arr = [1,3,5]
// Output: 4
// Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
// All sub-arrays sum are [1,4,9,3,8,5].
// Odd sums are [1,9,3,5] so the answer is 4.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 100
//

/**
 * @param {number[]} arr
 * @return {number}
 */
var numOfSubarrays = function(arr) {
    const mod = 1e9 + 7;
    let oddCount = 0;
    let evenCount = 1; // empty subarray
    let prefixSum = 0;
    let result = 0;
    for (const num of arr) {
        prefixSum += num;   
        if (prefixSum % 2 === 0) {
            result = (result + oddCount) % mod;
            evenCount++;
        }
        else {
            result = (result + evenCount) % mod;
            oddCount++;
        }
    }
    return result;  
};
