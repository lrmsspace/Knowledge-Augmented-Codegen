// Source: https://leetcode.com/problems/day-of-the-week/   |   Difficulty: Easy
//
// Problem Description:
// Given a date, return the corresponding day of the week for that date.
//
// The input is given as three integers representing the day, month and year respectively.
//
// Return the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.
//
// Example:
// Input: day = 31, month = 8, year = 2019
// Output: "Saturday"
//
// Constraints:
// The given dates are valid dates between the years 1971 and 2100.
//

class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        static const vector<string> daysOfWeek = {
            "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
        };
        
        // Zeller's Congruence algorithm
        if (month < 3) {
            month += 12;
            year -= 1;
        }
        
        int k = year % 100;
        int j = year / 100;
        
        int f = day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j);
        int dayOfWeekIndex = f % 7;
        
        // Zeller's formula gives: 0=Saturday, 1=Sunday, ..., 6=Friday
        // We need to adjust it to: 0=Sunday, 1=Monday, ..., 6=Saturday
        dayOfWeekIndex = (dayOfWeekIndex + 5) % 7;
        
        return daysOfWeek[dayOfWeekIndex];          
    }
};
