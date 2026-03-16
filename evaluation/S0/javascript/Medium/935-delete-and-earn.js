// Source: https://leetcode.com/problems/delete-and-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:
//
//
// 	Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
//
//
// Return the maximum number of points you can earn by applying the above operation some number of times.
//
// Example:
// Input: nums = [3,4,2]
// Output: 6
// Explanation: You can perform the following operations:
// - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
// - Delete 2 to earn 2 points. nums = [].
// You earn a total of 6 points.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 104
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var deleteAndEarn = function(nums) {
    const maxNum = Math.max(...nums);
    const points = new Array(maxNum + 1).fill(0);
    for (const num of nums) {
        points[num] += num;
    }

    let avoid = 0;
    let using = 0;

    for (let i = 0; i < points.length; i++) {
        let temp = avoid;
        avoid = Math.max(avoid, using);
        using = points[i] + temp;
    }

    return Math.max(avoid, using);
};