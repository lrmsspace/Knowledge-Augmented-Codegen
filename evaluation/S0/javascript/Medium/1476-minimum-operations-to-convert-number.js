// Source: https://leetcode.com/problems/minimum-operations-to-convert-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing distinct numbers, an integer start, and an integer goal. There is an integer x that is initially set to start, and you want to perform operations on x such that it is converted to goal. You can perform the following operation repeatedly on the number x:
//
// If 0 <= x <= 1000, then for any index i in the array (0 <= i < nums.length), you can set x to any of the following:
//
//
// 	x + nums[i]
// 	x - nums[i]
// 	x ^ nums[i] (bitwise-XOR)
//
//
// Note that you can use each nums[i] any number of times in any order. Operations that set x to be out of the range 0 <= x <= 1000 are valid, but no more operations can be done afterward.
//
// Return the minimum number of operations needed to convert x = start into goal, and -1 if it is not possible.
//
// Example:
// Input: nums = [2,4,12], start = 2, goal = 12
// Output: 2
// Explanation: We can go from 2 → 14 → 12 with the following 2 operations.
// - 2 + 12 = 14
// - 14 - 2 = 12
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-109 <= nums[i], goal <= 109
// 	0 <= start <= 1000
// 	start != goal
// 	All the integers in nums are distinct.
//

/**
 * @param {number[]} nums
 * @param {number} start
 * @param {number} goal
 * @return {number}
 */
var minimumOperations = function(nums, start, goal) {
    const queue = [];
    const visited = new Set();
    queue.push([start, 0]);
    visited.add(start);
    const limit = 1000;

    while (queue.length > 0) {
        const [current, steps] = queue.shift();
        if (current === goal) {
            return steps;
        }
        for (const num of nums) {
            const nextValues = [current + num, current - num, current ^ num];
            for (const next of nextValues) {
                if (next === goal) {
                    return steps + 1;
                }
                if (next >= 0 && next <= limit && !visited.has(next)) {
                    visited.add(next);
                    queue.push([next, steps + 1]);
                }
            }
        }
    }
    return -1;  
};
