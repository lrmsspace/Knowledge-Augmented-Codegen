// Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
//
// Problem Description:
// Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
//
// Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
//
// Given the integer r, return the maximum number of darts that can lie on the dartboard.
//
// Example:
// Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
// Output: 4
// Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
//
// Constraints:
// 1 <= darts.length <= 100
// 	darts[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the darts are unique
// 	1 <= r <= 5000
//

/**
 * @param {number[][]} darts
 * @param {number} r
 * @return {number}
 */
var numPoints = function(darts, r) {
    const n = darts.length;
    let maxCount = 1;
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            const [x1, y1] = darts[i];
            const [x2, y2] = darts[j];
            const d = Math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2);
            if (d > 2 * r) continue;
            const midX = (x1 + x2) / 2;
            const midY = (y1 + y2) / 2;
            const h = Math.sqrt(r ** 2 - (d / 2) ** 2);
            const offsetX = h * (y2 - y1) / d;
            const offsetY = h * (x1 - x2) / d;
            const centers = [[midX + offsetX, midY + offsetY], [midX - offsetX, midY - offset
Y]];
            for (const [cx, cy] of centers) {
                let count = 0;
                for (const [x, y] of darts) {
                    if ((x - cx) ** 2 + (y - cy) ** 2 <= r ** 2 + 1e-9) {
                        count++;
                    }
                }
                maxCount = Math.max(maxCount, count);
            }
        }
    }
    return maxCount;    
};
