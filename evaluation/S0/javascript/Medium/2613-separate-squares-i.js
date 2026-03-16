// Source: https://leetcode.com/problems/separate-squares-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted multiple times.
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
// Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1012.
//

/**
 * @param {number[][]} squares
 * @return {number}
 */
var separateSquares = function(squares) {
    const events = [];
    for (const [x, y, l] of squares) {
        events.push([y, l * l]);
        events.push([y + l, -l * l]);
    }
    events.sort((a, b) => a[0] - b[0]);
    let totalArea = 0;
    for (const [, area] of events) {
        totalArea += area;
    }
    let halfArea = totalArea / 2;
    let currentArea = 0;
    for (let i = 0; i < events.length - 1; i++) {
        currentArea += events[i][1];
        if (currentArea === halfArea) {
            return events[i][0];
        } else if (currentArea > halfArea) {
            const diff = currentArea - halfArea;
            const segmentLength = events[i + 1][0] - events[i][0];
            return events[i][0] - (diff / (events[i][1] / segmentLength));
        }
    }
    return 0;
};