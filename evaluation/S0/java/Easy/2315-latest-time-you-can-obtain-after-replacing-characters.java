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

class Solution {
    public String findLatestTime(String s) {
        char[] time = s.toCharArray();

        // Determine the hour part
        if (time[0] == '?' && time[1] == '?') {
            time[0] = '1';
            time[1] = '1';
        } else if (time[0] == '?') {
            if (time[1] <= '1') {
                time[0] = '1';
            } else {
                time[0] = '0';
            }
        } else if (time[1] == '?') {
            if (time[0] == '1') {
                time[1] = '1';
            } else {
                time[1] = '9';
            }
        }

        // Determine the minute part
        if (time[3] == '?' && time[4] == '?') {
            time[3] = '5';
            time[4] = '9';
        } else if (time[3] == '?') {
            time[3] = '5';
        } else if (time[4] == '?') {
            time[4] = '9';
        }

        return new String(time);            
    }
}
