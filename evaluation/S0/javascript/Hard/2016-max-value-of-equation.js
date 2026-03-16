// Source: https://leetcode.com/problems/max-value-of-equation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.
//
// Return the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
//
// It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.
//
// Example:
// Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
// Output: 4
// Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
// No other pairs satisfy the condition, so we return the max of 4 and 1.
//
// Constraints:
// 2 <= points.length <= 105
// 	points[i].length == 2
// 	-108 <= xi, yi <= 108
// 	0 <= k <= 2 * 108
// 	xi < xj for all 1 <= i < j <= points.length
// 	xi form a strictly increasing sequence.
//

/**
 * @param {number[][]} points
 * @param {number} k
 * @return {number}
 */
var findMaxValueOfEquation = function(points, k) {
    const deque = [];
    let maxValue = -Infinity;
    for (const [x, y] of points) {
        while (deque.length > 0 && x - points[deque[0]][0] > k) {
            deque.shift();
        }
        if (deque.length > 0) {
            const [prevX, prevY] = points[deque[0]];
            maxValue = Math.max(maxValue, prevY - prevX + y + x);
        }
        while (deque.length > 0 && points[deque[deque.length - 1]][1] - points[deque[deque.length - 1]][0] <= y - x) {
            deque.pop();
        }
        deque.push(points.indexOf([x, y]));
    }
    return maxValue;
};
