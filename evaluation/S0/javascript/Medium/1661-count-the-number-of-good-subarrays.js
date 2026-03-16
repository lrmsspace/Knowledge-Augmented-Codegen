// Source: https://leetcode.com/problems/count-the-number-of-good-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of good subarrays of nums.
//
// A subarray arr is good if there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,1,1,1,1], k = 10
// Output: 1
// Explanation: The only good subarray is the array nums itself.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countGood = function(nums, k) {
    let left = 0;
    let count = 0;
    let pairCount = 0;
    const freqMap = new Map();

    for (let right = 0; right < nums.length; right++) {
        const num = nums[right];
        const freq = freqMap.get(num) || 0;
        pairCount += freq;
        freqMap.set(num, freq + 1);

        while (pairCount >= k) {
            count += nums.length - right;
            const leftNum = nums[left];
            const leftFreq = freqMap.get(leftNum);
            freqMap.set(leftNum, leftFreq - 1);
            pairCount -= leftFreq - 1;
            left++;
        }
    }   

    return count;
};