// Source: https://leetcode.com/problems/minimum-time-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
//
// Example:
// Input: timePoints = ["23:59","00:00"]
// Output: 1
//
// Constraints:
// 2 <= timePoints.length <= 2 * 104
// 	timePoints[i] is in the format "HH:MM".
//

/**
 * @param {string[]} timePoints
 * @return {number}
 */
var findMinDifference = function(timePoints) {
    const minutes = timePoints.map(time => {
        const [hh, mm] = time.split(':').map(Number);
        return hh * 60 + mm;
    });
    minutes.sort((a, b) => a - b);
    let minDiff = 1440 + minutes[0] - minutes[minutes.length - 1];
    for (let i = 1; i < minutes.length; i++) {
        minDiff = Math.min(minDiff, minutes[i] - minutes[i - 1]);
    }
    return minDiff;
};
