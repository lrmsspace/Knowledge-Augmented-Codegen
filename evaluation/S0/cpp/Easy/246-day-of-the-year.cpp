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
public:
    int dayOfYear(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        vector<int> days_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            days_in_month[1] = 29; // February has 29 days in a leap year
        }

        int day_of_year = 0;
        for (int i = 0; i < month - 1; ++i) {
            day_of_year += days_in_month[i];
        }
        day_of_year += day;

        return day_of_year;         
    }
};
