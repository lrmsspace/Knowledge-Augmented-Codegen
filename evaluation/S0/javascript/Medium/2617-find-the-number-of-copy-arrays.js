// Source: https://leetcode.com/problems/find-the-number-of-copy-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array original of length n and a 2D array bounds of length n x 2, where bounds[i] = [ui, vi].
//
// You need to find the number of possible arrays copy of length n such that:
//
//
// 	(copy[i] - copy[i - 1]) == (original[i] - original[i - 1]) for 1 <= i <= n - 1.
// 	ui <= copy[i] <= vi for 0 <= i <= n - 1.
//
//
// Return the number of such arrays.
//
// Example:
// Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]
//
// Output: 2
//
// Explanation:
//
// The possible arrays are:
//
//
// 	[1, 2, 3, 4]
// 	[2, 3, 4, 5]
//
// Constraints:
// 2 <= n == original.length <= 105
// 	1 <= original[i] <= 109
// 	bounds.length == n
// 	bounds[i].length == 2
// 	1 <= bounds[i][0] <= bounds[i][1] <= 109
//

/**
 * @param {number[]} original
 * @param {number[][]} bounds
 * @return {number}
 */
var countArrays = function(original, bounds) {
    const mod = 1e9 + 7;
    const n = original.length;
    let totalCount = 1;
    for (let i = 1; i < n; i++) {
        const diff = original[i] - original[i - 1];
        const lowerBound = bounds[i][0] - bounds[i - 1][1];
        const upperBound = bounds[i][1] - bounds[i - 1][0];
        if (diff < lowerBound || diff > upperBound) {
            return 0;
        }
        totalCount = (totalCount * (Math.min(bounds[i][1], bounds[i - 1][1] + diff) - Math.max(bounds[i][0], bounds[i - 1][0] + diff) + 1)) % mod;
    }
    return totalCount;
};