// Source: https://leetcode.com/problems/matchsticks-to-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
//
// Return true if you can make this square and false otherwise.
//
// Example:
// Input: matchsticks = [1,1,2,2,2]
// Output: true
// Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
//
// Constraints:
// 1 <= matchsticks.length <= 15
// 	1 <= matchsticks[i] <= 108
//

/**
 * @param {number[]} matchsticks
 * @return {boolean}
 */
var makesquare = function(matchsticks) {
    const totalLength = matchsticks.reduce((a, b) => a + b, 0);
    if (totalLength % 4 !== 0) return false;
    const sideLength = totalLength / 4;
    matchsticks.sort((a, b) => b - a);
    const sides = new Array(4).fill(0);

    const backtrack = (index) => {
        if (index === matchsticks.length) {
            return sides.every(side => side === sideLength);
        }

        for (let i = 0; i < 4; i++) {
            if (sides[i] + matchsticks[index] <= sideLength) {
                sides[i] += matchsticks[index];
                if (backtrack(index + 1)) return true;
                sides[i] -= matchsticks[index];
            }
        }
        return false;
    };

    return backtrack(0);
};