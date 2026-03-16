// Source: https://leetcode.com/problems/largest-time-for-given-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given an array arr of 4 digits, find the latest 24-hour time that can be made using each digit exactly once.
//
// 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
//
// Return the latest 24-hour time in "HH:MM" format. If no valid time can be made, return an empty string.
//
// Example:
// Input: arr = [1,2,3,4]
// Output: "23:41"
// Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42", "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times, "23:41" is the latest.
//
// Constraints:
// arr.length == 4
// 	0 <= arr[i] <= 9
//

class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        string res = "";
        sort(arr.begin(), arr.end());
        do {
            int hours = arr[0] * 10 + arr[1];
            int minutes = arr[2] * 10 + arr[3];
            if (hours < 24 && minutes < 60) {
                string time = (hours < 10 ? "0" : "") + to_string(hours) + ":" +
                              (minutes < 10 ? "0" : "") + to_string(minutes);
                res = max(res, time);
            }
        } while (next_permutation(arr.begin(), arr.end()));
        return res;         
    }
};
