// Source: https://leetcode.com/problems/count-lattice-points-inside-a-circle/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array circles where circles[i] = [xi, yi, ri] represents the center (xi, yi) and radius ri of the ith circle drawn on a grid, return the number of lattice points that are present inside at least one circle.
//
// Note:
//
//
// 	A lattice point is a point with integer coordinates.
// 	Points that lie on the circumference of a circle are also considered to be inside it.
//
// Example:
// Input: circles = [[2,2,1]]
// Output: 5
// Explanation:
// The figure above shows the given circle.
// The lattice points present inside the circle are (1, 2), (2, 1), (2, 2), (2, 3), and (3, 2) and are shown in green.
// Other points such as (1, 1) and (1, 3), which are shown in red, are not considered inside the circle.
// Hence, the number of lattice points present inside at least one circle is 5.
//
// Constraints:
// 1 <= circles.length <= 200
// 	circles[i].length == 3
// 	1 <= xi, yi <= 100
// 	1 <= ri <= min(xi, yi)
//

/**
 * @param {number[][]} circles
 * @return {number}
 */
var countLatticePoints = function(circles) {
    const points = new Set();
    for (const [xCenter, yCenter, radius] of circles) {
        for (let x = xCenter - radius; x <= xCenter + radius; x++) {
            for (let y = yCenter - radius; y <= yCenter + radius; y++) {
                if ((x - xCenter) ** 2 + (y - yCenter) ** 2 <= radius ** 2) {
                    points.add(`${x},${y}`);
                }
            }
        }
    }
    return points.size;
};
