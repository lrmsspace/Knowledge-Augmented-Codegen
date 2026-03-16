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

class Solution {
    public int convertTime(String current, String correct) {
        int currH = Integer.parseInt(current.substring(0, 2));
        int currM = Integer.parseInt(current.substring(3, 5));
        int corrH = Integer.parseInt(correct.substring(0, 2));
        int corrM = Integer.parseInt(correct.substring(3, 5));

        int totalCurrMins = currH * 60 + currM;
        int totalCorrMins = corrH * 60 + corrM;

        int diff = totalCorrMins - totalCurrMins;

        int operations = 0;
        int[] increments = {60, 15, 5, 1};

        for (int inc : increments) {
            operations += diff / inc;
            diff = diff % inc;
        }

        return operations;          
    }
}
