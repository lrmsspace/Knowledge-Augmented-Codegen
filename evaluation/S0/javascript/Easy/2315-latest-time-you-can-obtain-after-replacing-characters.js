// Source: https://leetcode.com/problems/latest-time-you-can-obtain-after-replacing-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s representing a 12-hour format time where some of the digits (possibly none) are replaced with a "?".
//
// 12-hour times are formatted as "HH:MM", where HH is between 00 and 11, and MM is between 00 and 59. The earliest 12-hour time is 00:00, and the latest is 11:59.
//
// You have to replace all the "?" characters in s with digits such that the time we obtain by the resulting string is a valid 12-hour format time and is the latest possible.
//
// Return the resulting string.
//
// Example:
// Input: s = "1?:?4"
//
// Output: "11:54"
//
// Explanation: The latest 12-hour format time we can achieve by replacing "?" characters is "11:54".
//
// Constraints:
// s.length == 5
// 	s[2] is equal to the character ":".
// 	All characters except s[2] are digits or "?" characters.
// 	The input is generated such that there is at least one time between "00:00" and "11:59" that you can obtain after replacing the "?" characters.
//

/**
 * @param {string} s
 * @return {string}
 */
var findLatestTime = function(s) {
    let hoursTens = s[0];
    let hoursUnits = s[1];
    let minutesTens = s[3];
    let minutesUnits = s[4];
    // Determine the latest possible hours
    if (hoursTens === '?') {
        if (hoursUnits === '?' || parseInt(hoursUnits) <= 1) {
            hoursTens = '1';
        } else {
            hoursTens = '0';
        }
    }
    if (hoursUnits === '?') {
        if (hoursTens === '1') {
            hoursUnits = '1';
        } else {
            hoursUnits = '9';
        }
    }
    // Determine the latest possible minutes
    if (minutesTens === '?') {
        minutesTens = '5';
    }
    if (minutesUnits === '?') {
        minutesUnits = '9';
    }
    return `${hoursTens}${hoursUnits}:${minutesTens}${minutesUnits}`;   
};
