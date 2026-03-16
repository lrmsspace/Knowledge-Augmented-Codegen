// Source: https://leetcode.com/problems/count-days-without-meetings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer days representing the total number of days an employee is available for work (starting from day 1). You are also given a 2D array meetings of size n where, meetings[i] = [start_i, end_i] represents the starting and ending days of meeting i (inclusive).
//
// Return the count of days when the employee is available for work but no meetings are scheduled.
//
// Note: The meetings may overlap.
//
// Example:
// Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
//
// Output: 2
//
// Explanation:
//
// There is no meeting scheduled on the 4th and 8th days.
//
// Constraints:
// 1 <= days <= 109
// 	1 <= meetings.length <= 105
// 	meetings[i].length == 2
// 	1 <= meetings[i][0] <= meetings[i][1] <= days
//

/**
 * @param {number} days
 * @param {number[][]} meetings
 * @return {number}
 */
var countDays = function(days, meetings) {
    const dayCount = new Array(days + 1).fill(0);
    for (const [start, end] of meetings) {
        dayCount[start]++;
        if (end + 1 <= days) {
            dayCount[end + 1]--;
        }
    }
    for (let i = 1; i <= days; i++) {
        dayCount[i] += dayCount[i - 1];
    }
    let availableDays = 0;
    for (let i = 1; i <= days; i++) {
        if (dayCount[i] === 0) {
            availableDays++;
        }
    }
    return availableDays;
};