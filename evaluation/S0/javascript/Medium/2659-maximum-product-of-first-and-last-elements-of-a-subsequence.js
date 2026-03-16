// Source: https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer m.
//
// Return the maximum product of the first and last elements of any subsequence of nums of size m.
//
// Example:
// Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
//
// Output: 81
//
// Explanation:
//
// The subsequence [-9] has the largest product of the first and last elements: -9 * -9 = 81. Therefore, the answer is 81.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	1 <= m <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} m
 * @return {number}
 */
var maximumProduct = function(nums, m) {
    const sorted = nums.slice().sort((a, b) => a - b);
    const n = sorted.length;
    const candidates = [];
    for (let i = 0; i < m; i++) {
        candidates.push(sorted[i]);
    }
    for (let i = n - 1; i >= n - m; i--) {
        candidates.push(sorted[i]);
    }
    let maxProduct = -Infinity;
    for (let i = 0; i < candidates.length; i++) {
        for (let j = i; j < candidates.length; j++) {
            const product = candidates[i] * candidates[j];
            maxProduct = Math.max(maxProduct, product);
        }
    }
    return maxProduct;  
};
