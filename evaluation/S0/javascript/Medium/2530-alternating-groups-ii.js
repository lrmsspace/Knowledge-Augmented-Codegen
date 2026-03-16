// Source: https://leetcode.com/problems/alternating-groups-ii/   |   Difficulty: Medium
//
// Problem Description:
// There is a circle of red and blue tiles. You are given an array of integers colors and an integer k. The color of tile i is represented by colors[i]:
//
//
// 	colors[i] == 0 means that tile i is red.
// 	colors[i] == 1 means that tile i is blue.
//
//
// An alternating group is every k contiguous tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its left and right tiles).
//
// Return the number of alternating groups.
//
// Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
//
// Example:
// Input: colors = [0,1,0,1,0], k = 3
//
// Output: 3
//
// Explanation:
//
//
//
// Alternating groups:
//
// Constraints:
// 3 <= colors.length <= 105
// 	0 <= colors[i] <= 1
// 	3 <= k <= colors.length
//

/**
 * @param {number[]} colors
 * @param {number} k
 * @return {number}
 */
var numberOfAlternatingGroups = function(colors, k) {
    let count = 0;
    for (let i = 0; i < colors.length; i++) {
        let isAlternating = true;
        for (let j = 0; j < k; j++) {
            if (colors[(i + j) % colors.length] === colors[(i + j - 1 + colors.length) % colors.length]) {
                isAlternating = false;
                break;
            }
        }        if (isAlternating) {
            count++;
        }
    }
    return count;
};
