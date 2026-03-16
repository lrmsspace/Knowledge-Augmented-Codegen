// Source: https://leetcode.com/problems/rectangle-area-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.
//
// Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.
//
// Return the total area. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
// Output: 6
// Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
// From (1,1) to (2,2), the green and red rectangles overlap.
// From (1,0) to (2,3), all three rectangles overlap.
//
// Constraints:
// 1 <= rectangles.length <= 200
// 	rectanges[i].length == 4
// 	0 <= xi1, yi1, xi2, yi2 <= 109
// 	xi1 <= xi2
// 	yi1 <= yi2
// 	All rectangles have non zero area.
//

/**
 * @param {number[][]} rectangles
 * @return {number}
 */
var rectangleArea = function(rectangles) {
    const MOD = 1e9 + 7;
    const events = [];
    const ys = new Set();

    for (const [x1, y1, x2, y2] of rectangles) {
        events.push([x1, y1, y2, 1]);
        events.push([x2, y1, y2, -1]);
        ys.add(y1);
        ys.add(y2);
    }
    events.sort((a, b) => a[0] - b[0]);
    const sortedYs = Array.from(ys).sort((a, b) => a - b);
    const active = new Array(sortedYs.length).fill(0);
    let prevX = 0;
    let area = 0;

    for (const [x, y1, y2, type] of events) {
        let coveredLength = 0;
        for (let i = 0; i < active.length; i++) {
            if (active[i] > 0) {
                coveredLength += (i < active.length - 1 ? sortedYs[i + 1] : 0) - sortedYs[i];
            }
        }
        area = (area + coveredLength * (x - prevX)) % MOD;
        prevX = x;
        for (let i = 0; i < sortedYs.length; i++) {
            if (sortedYs[i] >= y1 && sortedYs[i] < y2) {
                active[i] += type;
            }
        }
    }
    return area;    
};
