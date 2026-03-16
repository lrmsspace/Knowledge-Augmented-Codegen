// Source: https://leetcode.com/problems/day-of-the-year/   |   Difficulty: Easy
//
// Problem Description:
// Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.
//
// Example:
// Input: date = "2019-01-09"
// Output: 9
// Explanation: Given date is the 9th day of the year in 2019.
//
// Constraints:
// date.length == 10
// 	date[4] == date[7] == '-', and all other date[i]'s are digits
// 	date represents a calendar date between Jan 1st, 1900 and Dec 31st, 2019.
//

class Solution {
    public int dayOfYear(String date) {
        String[] parts = date.split("-");
        int year = Integer.parseInt(parts[0]);
        int month = Integer.parseInt(parts[1]);
        int day = Integer.parseInt(parts[2]);

        int[] daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Check for leap year
        if (isLeapYear(year)) {
            daysInMonths[1] = 29;
        }

        int dayOfYear = 0;
        for (int i = 0; i < month - 1; i++) {
            dayOfYear += daysInMonths[i];
        }
        dayOfYear += day;

        return dayOfYear;           
    }
}
