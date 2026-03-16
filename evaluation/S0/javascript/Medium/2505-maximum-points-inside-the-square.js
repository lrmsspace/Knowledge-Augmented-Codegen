// Source: https://leetcode.com/problems/maximum-points-inside-the-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.
//
// A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.
//
// Return the maximum number of points contained in a valid square.
//
// Note:
//
//
// 	A point is considered to be inside the square if it lies on or within the square's boundaries.
// 	The side length of the square can be zero.
//
// Example:
// Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
//
// Output: 2
//
// Explanation:
//
// The square of side length 4 covers two points points[0] and points[1].
//
// Constraints:
// 1 <= s.length, points.length <= 105
// 	points[i].length == 2
// 	-109 <= points[i][0], points[i][1] <= 109
// 	s.length == points.length
// 	points consists of distinct coordinates.
// 	s consists only of lowercase English letters.
//

/**
 * @param {number[][]} points
 * @param {string} s
 * @return {number}
 */
var maxPointsInsideSquare = function(points, s) {
    const n = points.length;
    const tagMap = new Map();
    for (let i = 0; i < n; i++) {
        if (!tagMap.has(s[i])) {
            tagMap.set(s[i], []);
        }
        tagMap.get(s[i]).push(points[i]);
    }
    let maxPoints = 0;
    for (const [tag, coords] of tagMap.entries()) {                                             
        const xCoords = coords.map(coord => coord[0]);
        const yCoords = coords.map(coord => coord[1]);
        const minX = Math.min(...xCoords);
        const maxX = Math.max(...xCoords);
        const minY = Math.min(...yCoords);
        const maxY = Math.max(...yCoords);
        const sideLength = Math.max(maxX - minX, maxY - minY);
        let count = 0;
        for (const coord of coords) {
            if (Math.abs(coord[0]) <= sideLength / 2 && Math.abs(coord[1]) <= sideLength / 2) {
                count++;
            }
        }
        maxPoints = Math.max(maxPoints, count);
    }
    return maxPoints;   
};
