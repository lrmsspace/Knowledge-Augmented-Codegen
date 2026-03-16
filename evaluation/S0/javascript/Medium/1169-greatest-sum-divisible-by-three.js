// Source: https://leetcode.com/problems/greatest-sum-divisible-by-three/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.
//
// Example:
// Input: nums = [3,6,5,1,8]
// Output: 18
// Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
//
// Constraints:
// 1 <= nums.length <= 4 * 104
// 	1 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSumDivThree = function(nums) {
    let dp = [0, -Infinity, -Infinity];
    for (const num of nums) {
        const temp = dp.slice();
        for (let i = 0; i < 3; i++) {
            const newIndex = (i + num % 3) % 3;
            temp[newIndex] = Math.max(temp[newIndex], dp[i] + num);
        }
        dp = temp;
    }
    return dp[0];
        
};
