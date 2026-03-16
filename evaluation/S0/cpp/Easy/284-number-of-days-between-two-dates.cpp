// Source: https://leetcode.com/problems/number-of-days-between-two-dates/   |   Difficulty: Easy
//
// Problem Description:
// Write a program to count the number of days between two dates.
//
// The two dates are given as strings, their format is YYYY-MM-DD as shown in the examples.
//
// Example:
// Input: date1 = "2019-06-29", date2 = "2019-06-30"
// Output: 1
//
// Constraints:
// The given dates are valid dates between the years 1971 and 2100.
//

class Solution {
public:
    int daysBetweenDates(string date1, string date2) {
        auto toDays = [](const string& date) {
            int year = stoi(date.substr(0, 4));
            int month = stoi(date.substr(5, 2));
            int day = stoi(date.substr(8, 2));

            if (month < 3) {
                year--;
                month += 12;
            }

            return 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 306;
        };

        return abs(toDays(date1) - toDays(date2));          
    }
};
