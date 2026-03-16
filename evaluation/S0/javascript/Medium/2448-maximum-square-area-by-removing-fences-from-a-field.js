// Source: https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/   |   Difficulty: Medium
//
// Problem Description:
// There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.
//
// Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).
//
// Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.
//
// Example:
// Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
// Output: 4
// Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
//
// Constraints:
// 3 <= m, n <= 109
// 	1 <= hFences.length, vFences.length <= 600
// 	1 < hFences[i] < m
// 	1 < vFences[i] < n
// 	hFences and vFences are unique.
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number[]} hFences
 * @param {number[]} vFences
 * @return {number}
 */
var maximizeSquareArea = function(m, n, hFences, vFences) {
    const MOD = 1e9 + 7;
    hFences.push(1);
    hFences.push(m);
    vFences.push(1);
    vFences.push(n);
    hFences.sort((a, b) => a - b);
    vFences.sort((a, b) => a - b);
    let maxHGap = 0;
    for (let i = 1; i < hFences.length; i++) {
        maxHGap = Math.max(maxHGap, hFences[i] - hFences[i - 1]);
    }
    let maxVGap = 0;
    for (let i = 1; i < vFences.length; i++) {
        maxVGap = Math.max(maxVGap, vFences[i] - vFences[i - 1]);
    }
    const maxSide = Math.min(maxHGap, maxVGap) - 1;
    if (maxSide <= 0) {
        return -1;
    }
    return (maxSide * maxSide) % MOD;
};