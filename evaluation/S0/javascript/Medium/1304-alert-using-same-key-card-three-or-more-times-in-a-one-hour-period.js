// Source: https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/   |   Difficulty: Medium
//
// Problem Description:
// LeetCode company workers use key-cards to unlock office doors. Each time a worker uses their key-card, the security system saves the worker's name and the time when it was used. The system emits an alert if any worker uses the key-card three or more times in a one-hour period.
//
// You are given a list of strings keyName and keyTime where [keyName[i], keyTime[i]] corresponds to a person's name and the time when their key-card was used in a single day.
//
// Access times are given in the 24-hour time format "HH:MM", such as "23:51" and "09:49".
//
// Return a list of unique worker names who received an alert for frequent keycard use. Sort the names in ascending order alphabetically.
//
// Notice that "10:00" - "11:00" is considered to be within a one-hour period, while "22:51" - "23:52" is not considered to be within a one-hour period.
//
// Example:
// Input: keyName = ["daniel","daniel","daniel","luis","luis","luis","luis"], keyTime = ["10:00","10:40","11:00","09:00","11:00","13:00","15:00"]
// Output: ["daniel"]
// Explanation: "daniel" used the keycard 3 times in a one-hour period ("10:00","10:40", "11:00").
//
// Constraints:
// 1 <= keyName.length, keyTime.length <= 105
// 	keyName.length == keyTime.length
// 	keyTime[i] is in the format "HH:MM".
// 	[keyName[i], keyTime[i]] is unique.
// 	1 <= keyName[i].length <= 10
// 	keyName[i] contains only lowercase English letters.
//

/**
 * @param {string[]} keyName
 * @param {string[]} keyTime
 * @return {string[]}
 */
var alertNames = function(keyName, keyTime) {
    const timeMap = new Map();
    for (let i = 0; i < keyName.length; i++) {
        if (!timeMap.has(keyName[i])) {
            timeMap.set(keyName[i], []);
        }
        const [hours, minutes] = keyTime[i].split(':').map(Number);
        const totalMinutes = hours * 60 + minutes;
        timeMap.get(keyName[i]).push(totalMinutes);
    }
    const alertedNames = [];
    for (const [name, times] of timeMap.entries()) {
        times.sort((a, b) => a - b);
        for (let i = 2; i < times.length; i++) {
            if (times[i] - times[i - 2] <= 60) {
                alertedNames.push(name);
                break;
            }
        }
    }
    return alertedNames.sort();
};