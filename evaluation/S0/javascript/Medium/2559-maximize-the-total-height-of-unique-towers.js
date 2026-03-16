// Source: https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array maximumHeight, where maximumHeight[i] denotes the maximum height the ith tower can be assigned.
//
// Your task is to assign a height to each tower so that:
//
//
// 	The height of the ith tower is a positive integer and does not exceed maximumHeight[i].
// 	No two towers have the same height.
//
//
// Return the maximum possible total sum of the tower heights. If it's not possible to assign heights, return -1.
//
// Example:
// Input: maximumHeight = [2,3,4,3]
//
// Output: 10
//
// Explanation:
//
// We can assign heights in the following way: [1, 2, 4, 3].
//
// Constraints:
// 1 <= maximumHeight.length <= 105
// 	1 <= maximumHeight[i] <= 109
//

/**
 * @param {number[]} maximumHeight
 * @return {number}
 */
var maximumTotalSum = function(maximumHeight) {
    const n = maximumHeight.length;
    const sortedHeights = maximumHeight.slice().sort((a, b) => b - a);
    let totalSum = 0;
    let currentMaxHeight = Infinity;
    for (const height of sortedHeights) {
        const assignedHeight = Math.min(height, currentMaxHeight - 1);
        if (assignedHeight <= 0) {
            return -1;
        }
        totalSum += assignedHeight;
        currentMaxHeight = assignedHeight;
    }
    return totalSum;
};