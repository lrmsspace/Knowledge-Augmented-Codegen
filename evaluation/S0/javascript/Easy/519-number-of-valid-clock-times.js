// Source: https://leetcode.com/problems/number-of-valid-clock-times/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string of length 5 called time, representing the current time on a digital clock in the format "hh:mm". The earliest possible time is "00:00" and the latest possible time is "23:59".
//
// In the string time, the digits represented by the ? symbol are unknown, and must be replaced with a digit from 0 to 9.
//
// Return an integer answer, the number of valid clock times that can be created by replacing every ? with a digit from 0 to 9.
//
// Example:
// Input: time = "?5:00"
// Output: 2
// Explanation: We can replace the ? with either a 0 or 1, producing "05:00" or "15:00". Note that we cannot replace it with a 2, since the time "25:00" is invalid. In total, we have two choices.
//
// Constraints:
// time is a valid string of length 5 in the format "hh:mm".
// 	"00" <= hh <= "23"
// 	"00" <= mm <= "59"
// 	Some of the digits might be replaced with '?' and need to be replaced with digits from 0 to 9.
//

/**
 * @param {string} time
 * @return {number}
 */
var countTime = function(time) {
    let count = 1;
    if (time[0] === '?' && time[1] === '?') {
        count *= 24;
    }
    else if (time[0] === '?') {
        count *= time[1] <= '3' ? 3 : 2;
    }
    else if (time[1] === '?') {
        count *= time[0] === '2' ? 4 : 10;
    }
    if (time[3] === '?') {
        count *= 6;
    }
    if (time[4] === '?') {
        count *= 10;
    }
    return count;
};
