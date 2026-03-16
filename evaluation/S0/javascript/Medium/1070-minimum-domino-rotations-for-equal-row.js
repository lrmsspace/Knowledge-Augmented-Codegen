// Source: https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/   |   Difficulty: Medium
//
// Problem Description:
// In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
//
// We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
//
// Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.
//
// If it cannot be done, return -1.
//
// Example:
// Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
// Output: 2
// Explanation: 
// The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
// If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
//
// Constraints:
// 2 <= tops.length <= 2 * 104
// 	bottoms.length == tops.length
// 	1 <= tops[i], bottoms[i] <= 6
//

/**
 * @param {number[]} tops
 * @param {number[]} bottoms
 * @return {number}
 */
var minDominoRotations = function(tops, bottoms) {
    
    const n = tops.length;
    const count = (x) => {
        let topCount = 0;
        let bottomCount = 0;
        for (let i = 0; i < n; i++) {
            if (tops[i] !== x && bottoms[i] !== x) {
                return Infinity;
            } else if (tops[i] !== x) {
                topCount++;
            }
            else if (bottoms[i] !== x) {
                bottomCount++;
            }
        }   
        return Math.min(topCount, bottomCount);
    }   
    const rotationsForTop = count(tops[0]);
    const rotationsForBottom = count(bottoms[0]);
    const minRotations = Math.min(rotationsForTop, rotationsForBottom);
    return minRotations === Infinity ? -1 : minRotations;   
                
};
