// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
//
// Return the minimum possible sum of the area of these rectangles.
//
// Note that the rectangles are allowed to touch.
//
// Example:
// Input: grid = [[1,0,1],[1,1,1]]
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
// 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
// 	The 1 at (1, 1) is covered by a rectangle of area 1.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 30
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there are at least three 1's in grid.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minimumSum = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;

    const getArea = (r1, c1, r2, c2) => {
        let area = 0;
        for (let i = r1; i <= r2; i++) {
            for (let j = c1; j <= c2; j++) {
                if (grid[i][j] === 1) {
                    area++;
                }
            }
        }
        return area;
    };

    let minArea = Infinity;

    for (let r1 = 0; r1 < rows; r1++) {
        for (let c1 = 0; c1 < cols; c1++) {
            for (let r2 = r1; r2 < rows; r2++) {
                for (let c2 = c1; c2 < cols; c2++) {
                    const area = getArea(r1, c1, r2, c2);
                    if (area > 0) {
                        minArea = Math.min(minArea, area);
                    }
                }
            }
        }
    }

    return minArea;
};