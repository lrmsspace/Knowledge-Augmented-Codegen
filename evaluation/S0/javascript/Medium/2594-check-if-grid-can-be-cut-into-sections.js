// Source: https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the dimensions of an n x n grid, with the origin at the bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid. Each rectangle is defined as follows:
//
//
// 	(startx, starty): The bottom-left corner of the rectangle.
// 	(endx, endy): The top-right corner of the rectangle.
//
//
// Note that the rectangles do not overlap. Your task is to determine if it is possible to make either two horizontal or two vertical cuts on the grid such that:
//
//
// 	Each of the three resulting sections formed by the cuts contains at least one rectangle.
// 	Every rectangle belongs to exactly one section.
//
//
// Return true if such cuts can be made; otherwise, return false.
//
// Example:
// Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
//
// Output: true
//
// Explanation:
//
//
//
// The grid is shown in the diagram. We can make horizontal cuts at y = 2 and y = 4. Hence, output is true.
//
// Constraints:
// 3 <= n <= 109
// 	3 <= rectangles.length <= 105
// 	0 <= rectangles[i][0] < rectangles[i][2] <= n
// 	0 <= rectangles[i][1] < rectangles[i][3] <= n
// 	No two rectangles overlap.
//

/**
 * @param {number} n
 * @param {number[][]} rectangles
 * @return {boolean}
 */
var checkValidCuts = function(n, rectangles) {
    const horizontalCuts = new Set();
    const verticalCuts = new Set();
    for (const [startx, starty, endx, endy] of rectangles) {
        horizontalCuts.add(starty);
        horizontalCuts.add(endy);
        verticalCuts.add(startx);
        verticalCuts.add(endx);
    }
    if (horizontalCuts.size >= 3) {
        const sortedCuts = Array.from(horizontalCuts).sort((a, b) => a - b);
        for (let i = 1; i < sortedCuts.length - 1; i++) {
            const cut1 = sortedCuts[i - 1];
            const cut2 = sortedCuts[i];
            const cut3 = sortedCuts[i + 1];
            if (cut1 < cut2 && cut2 < cut3) {
                return true;
            }
        }
    }
    if (verticalCuts.size >= 3) {
        const sortedCuts = Array.from(verticalCuts).sort((a, b) => a - b);
        for (let i = 1; i < sortedCuts.length - 1; i++) {
            const cut1 = sortedCuts[i - 1];
            const cut2 = sortedCuts[i];
            const cut3 = sortedCuts[i + 1];
            if (cut1 < cut2 && cut2 < cut3) {
                return true;
            }
        }
    }
    return false;
};
