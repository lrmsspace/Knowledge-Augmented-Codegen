// Source: https://leetcode.com/problems/minimum-jumps-to-reach-home/   |   Difficulty: Medium
//
// Problem Description:
// A certain bug's home is on the x-axis at position x. Help them get there from position 0.
//
// The bug jumps according to the following rules:
//
//
// 	It can jump exactly a positions forward (to the right).
// 	It can jump exactly b positions backward (to the left).
// 	It cannot jump backward twice in a row.
// 	It cannot jump to any forbidden positions.
//
//
// The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
//
// Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
//
// Example:
// Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
// Output: 3
// Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
//
// Constraints:
// 1 <= forbidden.length <= 1000
// 	1 <= a, b, forbidden[i] <= 2000
// 	0 <= x <= 2000
// 	All the elements in forbidden are distinct.
// 	Position x is not forbidden.
//

/**
 * @param {number[]} forbidden
 * @param {number} a
 * @param {number} b
 * @param {number} x
 * @return {number}
 */
var minimumJumps = function(forbidden, a, b, x) {
    const forbiddenSet = new Set(forbidden);
    const visited = new Set();
    const queue = [];
    queue.push([0, 0, false]);
    visited.add("0,false");
    while (queue.length > 0) {
        const [position, jumps, lastJumpBackward] = queue.shift();
        if (position === x) {
            return jumps;
        }
        const forward = position + a;
        if (forward <= 6000 && !forbiddenSet.has(forward) && !visited.has(forward + ",false")) {
            visited.add(forward + ",false");
            queue.push([forward, jumps + 1, false]);
        }
        const backward = position - b;
        if (!lastJumpBackward && backward >= 0 && !forbiddenSet.has(backward) && !visited.has(backward + ",true")) {
            visited.add(backward + ",true");
            queue.push([backward, jumps + 1, true]);
        }
    }
    return -1;
};