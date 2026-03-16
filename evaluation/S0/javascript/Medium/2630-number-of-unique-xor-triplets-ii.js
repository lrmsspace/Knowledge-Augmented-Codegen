// Source: https://leetcode.com/problems/number-of-unique-xor-triplets-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
//
// Return the number of unique XOR triplet values from all possible triplets (i, j, k).
//
// Example:
// Input: nums = [1,3]
//
// Output: 2
//
// Explanation:
//
// The possible XOR triplet values are:
//
//
// 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
// 	(0, 0, 1) → 1 XOR 1 XOR 3 = 3
// 	(0, 1, 1) → 1 XOR 3 XOR 3 = 1
// 	(1, 1, 1) → 3 XOR 3 XOR 3 = 3
//
//
// The unique XOR values are {1, 3}. Thus, the output is 2.
//
// Constraints:
// 1 <= nums.length <= 1500
// 	1 <= nums[i] <= 1500
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var uniqueXorTriplets = function(nums) {
    const n = nums.length;
    const uniqueXors = new Set();
    for (let i = 0; i < n; i++) {
        for (let j = i; j < n; j++) {
            for (let k = j; k < n; k++) {
                const xorValue = nums[i] ^ nums[j] ^ nums[k];
                uniqueXors.add(xorValue);
            }
        }
    }
    return uniqueXors.size; 
};