// Source: https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and an integer target.
//
// Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [3,5,6,7], target = 9
// Output: 4
// Explanation: There are 4 subsequences that satisfy the condition.
// [3] -> Min value + max value <= target (3 + 3 <= 9)
// [3,5] -> (3 + 5 <= 9)
// [3,5,6] -> (3 + 6 <= 9)
// [3,6] -> (3 + 6 <= 9)
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= target <= 106
//

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var numSubseq = function(nums, target) {
    nums.sort((a, b) => a - b);
    const mod = 1e9 + 7;
    const n = nums.length;
    const pow = new Array(n).fill(0);
    pow[0] = 1;
    for (let i = 1; i < n; i++) {
        pow[i] = (pow[i - 1] * 2) % mod;
    }
    let left = 0;
    let right = n - 1;
    let result = 0;
    while (left <= right) {
        if (nums[left] + nums[right] <= target) {
            result = (result + pow[right - left]) % mod;
            left++;
        } else {
            right--;
        }
    }
    return result;
};