// Source: https://leetcode.com/problems/longest-square-streak-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. A subsequence of nums is called a square streak if:
//
//
// 	The length of the subsequence is at least 2, and
// 	after sorting the subsequence, each element (except the first element) is the square of the previous number.
//
//
// Return the length of the longest square streak in nums, or return -1 if there is no square streak.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [4,3,6,16,8,2]
// Output: 3
// Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes [2,4,16].
// - 4 = 2 * 2.
// - 16 = 4 * 4.
// Therefore, [4,16,2] is a square streak.
// It can be shown that every subsequence of length 4 is not a square streak.
//
// Constraints:
// 2 <= nums.length <= 105
// 	2 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var longestSquareStreak = function(nums) {
    const numSet = new Set(nums);
    let longestStreak = -1;
    for (const num of nums) {
        if (!numSet.has(Math.sqrt(num))) {
            let currentNum = num;
            let currentStreak = 0;
            while (numSet.has(currentNum)) {
                currentStreak++;
                currentNum *= currentNum;
            }

            if (currentStreak >= 2) {
                longestStreak = Math.max(longestStreak, currentStreak);
            }
        }
    }
    return longestStreak;
};
