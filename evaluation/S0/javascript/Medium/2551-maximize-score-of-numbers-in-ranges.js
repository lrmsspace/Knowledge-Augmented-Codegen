// Source: https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers start and an integer d, representing n intervals [start[i], start[i] + d].
//
// You are asked to choose n integers where the ith integer must belong to the ith interval. The score of the chosen integers is defined as the minimum absolute difference between any two integers that have been chosen.
//
// Return the maximum possible score of the chosen integers.
//
// Example:
// Input: start = [6,0,3], d = 2
//
// Output: 4
//
// Explanation:
//
// The maximum possible score can be obtained by choosing integers: 8, 0, and 4. The score of these chosen integers is min(|8 - 0|, |8 - 4|, |0 - 4|) which equals 4.
//
// Constraints:
// 2 <= start.length <= 105
// 	0 <= start[i] <= 109
// 	0 <= d <= 109
//

/**
 * @param {number[]} start
 * @param {number} d
 * @return {number}
 */
var maxPossibleScore = function(start, d) {
    const n = start.length;
    const intervals = start.map(s => [s, s + d]);
    intervals.sort((a, b) => a[0] - b[0]);
    let low = 0;
    let high = d;
    while (low < high) {
        const mid = Math.floor((low + high + 1) / 2);
        let prev = intervals[0][0];
        let valid = true;
        for (let i = 1; i < n; i++) {
            const [start, end] = intervals[i];
            if (prev + mid > end) {
                valid = false;
                break;
            }
            prev = Math.max(prev + mid, start);
        }
        if (valid) {
            low = mid;
        }
        else {            high = mid - 1;
        }
    }
    return low;
        
};
