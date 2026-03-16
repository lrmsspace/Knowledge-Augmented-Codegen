// Source: https://leetcode.com/problems/subarray-sums-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [4,5,0,-2,-3,1], k = 5
// Output: 7
// Explanation: There are 7 subarrays with a sum divisible by k = 5:
// [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	-104 <= nums[i] <= 104
// 	2 <= k <= 104
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var subarraysDivByK = function(nums, k) {
    
    let count = 0;
    const modCount = new Array(k).fill(0);

    modCount[0] = 1; // There's one way to have a sum of 0 (the empty subarray)

    let prefixSum = 0;

    for (let num of nums) {
        prefixSum += num;
        let mod = ((prefixSum % k) + k) % k; // Handle negative mods
        count += modCount[mod];
        modCount[mod]++;
    }

    return count;   
    
};
