// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
//
// Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// Example:
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
//
// Output: [2,3]
//
// Explanation:
//
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
//
// Constraints:
// 1 <= intevals.length <= 5 * 104
// 	intervals[i].length == 3
// 	intervals[i] = [li, ri, weighti]
// 	1 <= li <= ri <= 109
// 	1 <= weighti <= 109
//

/**
 * @param {number[][]} intervals
 * @return {number[]}
 */
var maximumWeight = function(intervals) {
    intervals.sort((a, b) => a[1] - b[1]);
    const n = intervals.length;
    const dp = Array.from({ length: n + 1 }, () => Array(5).fill(0));
    const prev = Array.from({ length: n }, () => -1);
    for (let i = 0; i < n; i++) {
        let left = 0, right = i - 1;
        while (left <= right) {
            const mid = Math.floor((left + right) / 2);
            if (intervals[mid][1] < intervals[i][0]) {
                prev[i] = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    for (let i = 1; i <= n; i++) {  
        for (let j = 1; j <= 4; j++) {
            dp[i][j] = dp[i - 1][j];
            const includeWeight = intervals[i - 1][2] + (prev[i - 1] !== -1 ? dp[prev[i - 1] + 1][j - 1] : 0);
            if (includeWeight > dp[i][j]) {
                dp[i][j] = includeWeight;
            }
        }
    }
    const result = [];
    let j = 4;
    for (let i = n; i > 0 && j > 0; i--) {
        if (dp[i][j] !== dp[i - 1][j]) {
            result.push(i - 1);
            j--;
            i = prev[i - 1] + 1;
        }
    }
    result.reverse();
    return result;  
};
