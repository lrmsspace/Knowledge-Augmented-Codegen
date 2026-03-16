// Source: https://leetcode.com/problems/falling-squares/   |   Difficulty: Hard
//
// Problem Description:
// There are several squares being dropped onto the X-axis of a 2D plane.
//
// You are given a 2D integer array positions where positions[i] = [lefti, sideLengthi] represents the ith square with a side length of sideLengthi that is dropped with its left edge aligned with X-coordinate lefti.
//
// Each square is dropped one at a time from a height above any landed squares. It then falls downward (negative Y direction) until it either lands on the top side of another square or on the X-axis. A square brushing the left/right side of another square does not count as landing on it. Once it lands, it freezes in place and cannot be moved.
//
// After each square is dropped, you must record the height of the current tallest stack of squares.
//
// Return an integer array ans where ans[i] represents the height described above after dropping the ith square.
//
// Example:
// Input: positions = [[1,2],[2,3],[6,1]]
// Output: [2,5,5]
// Explanation:
// After the first drop, the tallest stack is square 1 with a height of 2.
// After the second drop, the tallest stack is squares 1 and 2 with a height of 5.
// After the third drop, the tallest stack is still squares 1 and 2 with a height of 5.
// Thus, we return an answer of [2, 5, 5].
//
// Constraints:
// 1 <= positions.length <= 1000
// 	1 <= lefti <= 108
// 	1 <= sideLengthi <= 106
//

/**
 * @param {number[][]} positions
 * @return {number[]}
 */
var fallingSquares = function(positions) {
    



    let heights = [];
    let maxHeight = 0;

    for (let [left, side] of positions) {
        let right = left + side;
        let currentHeight = side; // Start with the height of the current square

        // Check for overlaps with previously dropped squares
        for (let [prevLeft, prevSide] of heights) {
            let prevRight = prevLeft + prevSide;
            // If there is an overlap, update the current height
            if (prevLeft < right && prevRight > left) {
                currentHeight = Math.max(currentHeight, prevSide + side);
            }
        }
        heights.push([left, currentHeight]);
        maxHeight = Math.max(maxHeight, currentHeight);
        heights.push([left, currentHeight]);
        maxHeight = Math.max(maxHeight, currentHeight);
        heights.push([left, currentHeight]);
        maxHeight = Math.max(maxHeight, currentHeight);
        heights.push([left, currentHeight]);
        maxHeight = Math.max(maxHeight, currentHeight);
        heights.push([left, currentHeight]);
        maxHeight = Math.max(maxHeight, currentHeight);
        heights.push([left, currentHeight]);
        
    }
    return heights.map(([_, height]) => height);    
    
};
