// Source: https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array nums. Your task is to select a complete subset from nums where every pair of selected indices multiplied is a perfect square,. i. e. if you select ai and aj, i * j must be a perfect square.
//
// Return the sum of the complete subset with the maximum sum.
//
// Example:
// Input: nums = [8,7,3,5,7,2,4,9]
//
// Output: 16
//
// Explanation:
//
// We select elements at indices 2 and 8 and 2 * 8 is a perfect square.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumSum = function(nums) {
    const n = nums.length;
    const groups = {};
    for (let i = 1; i <= n; i++) {
        let j = 1;
        while (j * j < i) {
            if (i % (j * j) === 0) {
                i /= j * j;
            } else {
                j++;
            }
        }
        if (!groups[i]) {
            groups[i] = 0;
        }
        groups[i] += nums[i - 1];
    }
    let maxSum = 0;
    for (const key in groups) {
        maxSum = Math.max(maxSum, groups[key]);
    }
    return maxSum;  
};
