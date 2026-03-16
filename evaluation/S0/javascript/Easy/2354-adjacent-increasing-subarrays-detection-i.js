// Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums of n integers and an integer k, determine whether there exist two adjacent subarrays of length k such that both subarrays are strictly increasing. Specifically, check if there are two subarrays starting at indices a and b (a < b), where:
//
//
// 	Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
// 	The subarrays must be adjacent, meaning b = a + k.
//
//
// Return true if it is possible to find two such subarrays, and false otherwise.
//
// Example:
// Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3
//
// Output: true
//
// Explanation:
//
//
// 	The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
// 	The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
// 	These two subarrays are adjacent, so the result is true.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 < 2 * k <= nums.length
// 	-1000 <= nums[i] <= 1000
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {boolean}
 */
var hasIncreasingSubarrays = function(nums, k) {
    const n = nums.length;
    for (let i = 0; i <= n - 2 * k; i++) {
        let firstIncreasing = true;
        let secondIncreasing = true;
        for (let j = 0; j < k - 1; j++) {
            if (nums[i + j] >= nums[i + j + 1]) {
                firstIncreasing = false;
                break;
            }
        }
        for (let j = 0; j < k - 1; j++) {
            if (nums[i + k + j] >= nums[i + k + j + 1]) {
                secondIncreasing = false;
                break;
            }
        }
        if (firstIncreasing && secondIncreasing) {
            return true;
        }
    }
    return false;
};
