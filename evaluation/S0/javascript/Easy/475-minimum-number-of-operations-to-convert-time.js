// Source: https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings current and correct representing two 24-hour times.
//
// 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
//
// In one operation you can increase the time current by 1, 5, 15, or 60 minutes. You can perform this operation any number of times.
//
// Return the minimum number of operations needed to convert current to correct.
//
// Example:
// Input: current = "02:30", correct = "04:35"
// Output: 3
// Explanation:
// We can convert current to correct in 3 operations as follows:
// - Add 60 minutes to current. current becomes "03:30".
// - Add 60 minutes to current. current becomes "04:30".
// - Add 5 minutes to current. current becomes "04:35".
// It can be proven that it is not possible to convert current to correct in fewer than 3 operations.
//
// Constraints:
// current and correct are in the format "HH:MM"
// 	current <= correct
//

/**
 * @param {string} current
 * @param {string} correct
 * @return {number}
 */
var convertTime = function(current, correct) {
    const [currentHours, currentMinutes] = current.split(':').map(Number);
    const [correctHours, correctMinutes] = correct.split(':').map(Number);
    let currentTotalMinutes = currentHours * 60 + currentMinutes;
    let correctTotalMinutes = correctHours * 60 + correctMinutes;
    let diff = correctTotalMinutes - currentTotalMinutes;
    let operations = 0;
    const increments = [60, 15, 5, 1];
    for (const increment of increments) {
        operations += Math.floor(diff / increment);
        diff %= increment;
    }
    return operations;
};