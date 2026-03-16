// Source: https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers arr and an integer target.
//
// You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
//
// Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
//
// Example:
// Input: arr = [3,2,2,4,3], target = 3
// Output: 2
// Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 1000
// 	1 <= target <= 108
//

/**
 * @param {number[]} arr
 * @param {number} target
 * @return {number}
 */
var minSumOfLengths = function(arr, target) {
    const n = arr.length;
    const prefixSumMap = new Map();
    prefixSumMap.set(0, -1);
    let prefixSum = 0;
    const dp = new Array(n).fill(Infinity);
    let minLength = Infinity;
    let result = Infinity;
    for (let i = 0; i < n; i++) {
        prefixSum += arr[i];
        if (prefixSumMap.has(prefixSum - target)) {
            const startIdx = prefixSumMap.get(prefixSum - target) + 1;
            const currentLength = i - startIdx + 1;
            if (startIdx > 0 && dp[startIdx - 1] !== Infinity) {
                result = Math.min(result, currentLength + dp[startIdx - 1]);
            }
            minLength = Math.min(minLength, currentLength);
        }
        dp[i] = minLength;
        prefixSumMap.set(prefixSum, i);
    }
    return result === Infinity ? -1 : result;
        
};
