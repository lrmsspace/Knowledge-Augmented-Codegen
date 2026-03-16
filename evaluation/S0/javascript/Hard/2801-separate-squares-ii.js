// Source: https://leetcode.com/problems/separate-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted only once in this version.
//
// Example:
// Input: squares = [[0,0,1],[2,2,1]]
//
// Output: 1.00000
//
// Explanation:
//
//
//
// Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1015.
//

/**
 * @param {number[][]} squares
 * @return {number}
 */
var separateSquares = function(squares) {
    const events = [];
    for (const [x, y, l] of squares) {
        events.push([y, x, x + l, 1]); // square starts
        events.push([y + l, x, x + l, -1]); // square ends
    }
    events.sort((a, b) => a[0] - b[0]);

    const activeIntervals = [];
    let prevY = 0;
    let totalArea = 0;
    const areaAtY = [];
    for (const [y, xStart, xEnd, type] of events) {
        const height = y - prevY;
        if (height > 0) {
            let width = 0;
            let lastX = -1;
            activeIntervals.sort((a, b) => a[0] - b[0]);
            for (const [start, end] of activeIntervals) {
                const effectiveStart = Math.max(start, lastX);
                if (end > effectiveStart) {
                    width += end - effectiveStart;
                    lastX = end;
                }
            }
            const area = width * height;
            totalArea += area;
            areaAtY.push([prevY, totalArea]);
        }
        if (type === 1) {
            activeIntervals.push([xStart, xEnd]);
        }
        else {
            const index = activeIntervals.findIndex(interval => interval[0] === xStart && interval[1] === xEnd);
            activeIntervals.splice(index, 1);
        }
        prevY = y;
    }
    const halfArea = totalArea / 2;
    let left = 0, right = areaAtY.length - 1;
    let resultY = 0;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (areaAtY[mid][1] < halfArea) {
            left = mid + 1;
        }
        else {
            resultY = areaAtY[mid][0];
            right = mid - 1;
        }
    }
    return resultY;
};
