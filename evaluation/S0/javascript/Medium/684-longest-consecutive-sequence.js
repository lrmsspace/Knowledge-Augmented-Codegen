// Source: https://leetcode.com/problems/longest-consecutive-sequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in O(n) time.
//
// Example:
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
//
// Constraints:
// 0 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var longestConsecutive = function(nums) {
    const numSet = new Set(nums);
    let longestStreak = 0;
    for (const num of numSet) {
        if (!numSet.has(num - 1)) {
            let currentNum = num;
            let currentStreak = 1;
            while (numSet.has(currentNum + 1)) {
                currentNum++;
                currentStreak++;
            }
            longestStreak = Math.max(longestStreak, currentStreak);
        }
    }
    return longestStreak;
};