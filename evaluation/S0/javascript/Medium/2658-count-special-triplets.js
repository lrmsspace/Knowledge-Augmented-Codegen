// Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// A special triplet is defined as a triplet of indices (i, j, k) such that:
//
//
// 	0 <= i < j < k < n, where n = nums.length
// 	nums[i] == nums[j] * 2
// 	nums[k] == nums[j] * 2
//
//
// Return the total number of special triplets in the array.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [6,3,6]
//
// Output: 1
//
// Explanation:
//
// The only special triplet is (i, j, k) = (0, 1, 2), where:
//
//
// 	nums[0] = 6, nums[1] = 3, nums[2] = 6
// 	nums[0] = nums[1] * 2 = 3 * 2 = 6
// 	nums[2] = nums[1] * 2 = 3 * 2 = 6
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var specialTriplets = function(nums) {
    const mod = 1e9 + 7;
    const count = new Map();
    let result = 0;
    for (const num of nums) {
        const half = num / 2;
        if (num % 2 === 0 && count.has(half)) {
            result = (result + count.get(half)) % mod;
        }
        count.set(num, (count.get(num) || 0) + 1);
    }
    return result;  
};