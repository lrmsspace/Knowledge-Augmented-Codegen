// Source: https://leetcode.com/problems/valid-square/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.
//
// The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.
//
// A valid square has four equal sides with positive length and four equal angles (90-degree angles).
//
// Example:
// Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// Output: true
//
// Constraints:
// p1.length == p2.length == p3.length == p4.length == 2
// 	-104 <= xi, yi <= 104
//

/**
 * @param {number[]} p1
 * @param {number[]} p2
 * @param {number[]} p3
 * @param {number[]} p4
 * @return {boolean}
 */
var validSquare = function(p1, p2, p3, p4) {
    const distSq = (a, b) => {
        return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2;
    };

    const points = [p1, p2, p3, p4];
    const dists = [];   
    for (let i = 0; i < points.length; i++) {
        for (let j = i + 1; j < points.length; j++) {
            dists.push(distSq(points[i], points[j]));
        }
    }

    dists.sort((a, b) => a - b);
    const side = dists[0];
    if (side === 0) return false; // overlapping points
    for (let i = 0; i < 4; i++) {
        if (dists[i] !== side) return false;
    }                                                   
    for (let i = 4; i < 6; i++) {
        if (dists[i] !== 2 * side) return false;
    }
    return true;    
};
