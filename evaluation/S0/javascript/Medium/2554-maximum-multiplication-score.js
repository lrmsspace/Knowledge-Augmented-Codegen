// Source: https://leetcode.com/problems/maximum-multiplication-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array a of size 4 and another integer array b of size at least 4.
//
// You need to choose 4 indices i0, i1, i2, and i3 from the array b such that i0 < i1 < i2 < i3. Your score will be equal to the value a[0] * b[i0] + a[1] * b[i1] + a[2] * b[i2] + a[3] * b[i3].
//
// Return the maximum score you can achieve.
//
// Example:
// Input: a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7]
//
// Output: 26
//
// Explanation:
// We can choose the indices 0, 1, 2, and 5. The score will be 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26.
//
// Constraints:
// a.length == 4
// 	4 <= b.length <= 105
// 	-105 <= a[i], b[i] <= 105
//

/**
 * @param {number[]} a
 * @param {number[]} b
 * @return {number}
 */
var maxScore = function(a, b) {
    const n = b.length;
    const dp = Array.from({ length: n }, () => Array(4).fill(-Infinity));
    for (let i = 0; i < n; i++) {
        dp[i][0] = a[0] * b[i];
        for (let j = 1; j < 4; j++) {
            for (let k = 0; k < i; k++) {
                dp[i][j] = Math.max(dp[i][j], dp[k][j - 1] + a[j] * b[i]);
            }
        }
    }
    let maxScore = -Infinity;
    for (let i = 0; i < n; i++) {
        maxScore = Math.max(maxScore, dp[i][3]);
    }
    return maxScore;    
};
