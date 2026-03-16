// Source: https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D 0-indexed integer array dimensions.
//
// For all indices i, 0 <= i < dimensions.length, dimensions[i][0] represents the length and dimensions[i][1] represents the width of the rectangle i.
//
// Return the area of the rectangle having the longest diagonal. If there are multiple rectangles with the longest diagonal, return the area of the rectangle having the maximum area.
//
// Example:
// Input: dimensions = [[9,3],[8,6]]
// Output: 48
// Explanation: 
// For index = 0, length = 9 and width = 3. Diagonal length = sqrt(9 * 9 + 3 * 3) = sqrt(90) ≈ 9.487.
// For index = 1, length = 8 and width = 6. Diagonal length = sqrt(8 * 8 + 6 * 6) = sqrt(100) = 10.
// So, the rectangle at index 1 has a greater diagonal length therefore we return area = 8 * 6 = 48.
//
// Constraints:
// 1 <= dimensions.length <= 100
// 	dimensions[i].length == 2
// 	1 <= dimensions[i][0], dimensions[i][1] <= 100
//

/**
 * @param {number[][]} dimensions
 * @return {number}
 */
var areaOfMaxDiagonal = function(dimensions) {
    let maxDiagonal = 0;
    let maxArea = 0;
    for (const [length, width] of dimensions) {
        const diagonal = Math.sqrt(length * length + width * width);
        const area = length * width;
        if (diagonal > maxDiagonal || (diagonal === maxDiagonal && area > maxArea)) {
            maxDiagonal = diagonal;
            maxArea = area;
        }
    }
    return maxArea;
};  