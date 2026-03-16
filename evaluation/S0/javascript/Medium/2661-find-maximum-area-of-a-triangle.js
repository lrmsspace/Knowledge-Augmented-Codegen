// Source: https://leetcode.com/problems/find-maximum-area-of-a-triangle/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array coords of size n x 2, representing the coordinates of n points in an infinite Cartesian plane.
//
// Find twice the maximum area of a triangle with its corners at any three elements from coords, such that at least one side of this triangle is parallel to the x-axis or y-axis. Formally, if the maximum area of such a triangle is A, return 2 * A.
//
// If no such triangle exists, return -1.
//
// Note that a triangle cannot have zero area.
//
// Example:
// Input: coords = [[1,1],[1,2],[3,2],[3,3]]
//
// Output: 2
//
// Explanation:
//
//
//
// The triangle shown in the image has a base 1 and height 2. Hence its area is 1/2 * base * height = 1.
//
// Constraints:
// 1 <= n == coords.length <= 105
// 	1 <= coords[i][0], coords[i][1] <= 106
// 	All coords[i] are unique.
//

/**
 * @param {number[][]} coords
 * @return {number}
 */
var maxArea = function(coords) {
    const xMap = new Map();
    const yMap = new Map();
    for (const [x, y] of coords) {
        if (!xMap.has(x)) {
            xMap.set(x, []);
        }
        xMap.get(x).push(y);
        if (!yMap.has(y)) {
            yMap.set(y, []);
        }
        yMap.get(y).push(x);
    }
    let maxArea = -1;
    for (const [x, ys] of xMap.entries()) {
        ys.sort((a, b) => a - b);
        for (let i = 0; i < ys.length; i++) {
            for (let j = i + 1; j < ys.length; j++) {
                const y1 = ys[i];
                const y2 = ys[j];
                const height = y2 - y1;
                const xs1 = yMap.get(y1);
                const xs2 = yMap.get(y2);
                let left = 0;
                let right = 0;
                while (left < xs1.length && right < xs2.length) {
                    if (xs1[left] === xs2[right]) {
                        const base = Math.abs(xs1[left] - x);
                        maxArea = Math.max(maxArea, base * height);
                        left++;
                        right++;
                    } else if (xs1[left] < xs2[right]) {
                        left++;
                    } else {
                        right++;
                    }
                }
            }
        }
    }
    return maxArea;
};