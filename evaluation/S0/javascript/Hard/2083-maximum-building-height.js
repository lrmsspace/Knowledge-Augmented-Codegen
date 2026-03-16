// Source: https://leetcode.com/problems/maximum-building-height/   |   Difficulty: Hard
//
// Problem Description:
// You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.
//
// However, there are city restrictions on the heights of the new buildings:
//
//
// 	The height of each building must be a non-negative integer.
// 	The height of the first building must be 0.
// 	The height difference between any two adjacent buildings cannot exceed 1.
//
//
// Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.
//
// It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.
//
// Return the maximum possible height of the tallest building.
//
// Example:
// Input: n = 5, restrictions = [[2,1],[4,1]]
// Output: 2
// Explanation: The green area in the image indicates the maximum allowed height for each building.
// We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
//
// Constraints:
// 2 <= n <= 109
// 	0 <= restrictions.length <= min(n - 1, 105)
// 	2 <= idi <= n
// 	idi is unique.
// 	0 <= maxHeighti <= 109
//

/**
 * @param {number} n
 * @param {number[][]} restrictions
 * @return {number}
 */
var maxBuilding = function(n, restrictions) {
    restrictions.push([1, 0]);
    restrictions.push([n, n - 1]);
    restrictions.sort((a, b) => a[0] - b[0]);
    for (let i = 1; i < restrictions.length; i++) {
        const [prevId, prevMax] = restrictions[i - 1];
        const [currId, currMax] = restrictions[i];
        const maxAllowed = prevMax + (currId - prevId);
        if (currMax > maxAllowed) {
            restrictions[i][1] = maxAllowed;
        }
    }
    for (let i = restrictions.length - 2; i >= 0; i--) {
        const [nextId, nextMax] = restrictions[i + 1];
        const [currId, currMax] = restrictions[i];
        const maxAllowed = nextMax + (nextId - currId);
        if (currMax > maxAllowed) {
            restrictions[i][1] = maxAllowed;
        }
    }
    let maxHeight = 0;
    for (let i = 1; i < restrictions.length; i++) {
        const [prevId, prevMax] = restrictions[i - 1];
        const [currId, currMax] = restrictions[i];
        const distance = currId - prevId;
        const heightDiff = Math.abs(currMax - prevMax);
        if (heightDiff >= distance) {
            maxHeight = Math.max(maxHeight, Math.max(prevMax, currMax) + distance - heightDiff);
        }
        maxHeight = Math.max(maxHeight, Math.min(prevMax, currMax) + Math.floor((distance - heightDiff) / 2));
    }
    return maxHeight;
};
