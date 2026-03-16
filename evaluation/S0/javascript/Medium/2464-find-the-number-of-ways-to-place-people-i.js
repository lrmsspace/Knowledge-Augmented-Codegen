// Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
//
// Count the number of pairs of points (A, B), where
//
//
// 	A is on the upper left side of B, and
// 	there are no other points in the rectangle (or line) they make (including the border), except for the points A and B.
//
//
// Return the count.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
//
// Output: 0
//
// Explanation:
//
//
//
// There is no way to choose A and B such that A is on the upper left side of B.
//
// Constraints:
// 2 <= n <= 50
// 	points[i].length == 2
// 	0 <= points[i][0], points[i][1] <= 50
// 	All points[i] are distinct.
//

/**
 * @param {number[][]} points
 * @return {number}
 */
var numberOfPairs = function(points) {
    let count = 0;
    const n = points.length;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                const [x1, y1] = points[i];
                const [x2, y2] = points[j];
                if (x1 < x2 && y1 > y2) {
                    let isValid = true;
                    for (let k = 0; k < n; k++) {
                        if (k !== i && k !== j) {
                            const [xk, yk] = points[k];
                            if (xk >= x1 && xk <= x2 && yk <= y1 && yk >= y2) {
                                isValid = false;
                                break;
                            }
                        }
                    }
                    if (isValid) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
};