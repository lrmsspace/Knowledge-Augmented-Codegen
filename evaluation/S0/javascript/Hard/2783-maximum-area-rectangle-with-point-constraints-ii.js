// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= xCoord.length == yCoord.length <= 2 * 105
// 	0 <= xCoord[i], yCoord[i] <= 8 * 107
// 	All the given points are unique.
//

/**
 * @param {number[]} xCoord
 * @param {number[]} yCoord
 * @return {number}
 */
var maxRectangleArea = function(xCoord, yCoord) {
    const n = xCoord.length;
    const pointsSet = new Set();
    for (let i = 0; i < n; i++) {
        pointsSet.add(`${xCoord[i]}#${yCoord[i]}`);
    }
    let maxArea = -1;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (xCoord[i] !== xCoord[j] && yCoord[i] !== yCoord[j]) {
                const p1 = `${xCoord[i]}#${yCoord[j]}`;
                const p2 = `${xCoord[j]}#${yCoord[i]}`;
                if (pointsSet.has(p1) && pointsSet.has(p2)) {
                    const area = Math.abs(xCoord[i] - xCoord[j]) * Math.abs(yCoord[i] - yCoord[j]);
                    maxArea = Math.max(maxArea, area);
                }
            }
        }
    }    return maxArea;    
};
