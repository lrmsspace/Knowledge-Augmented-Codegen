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
    public String dayOfTheWeek(int day, int month, int year) {
        String[] days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        int[] monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Calculate total days from 1971/01/01 to the given date
        int totalDays = 0;
        
        // Add days for the years
        for (int y = 1971; y < year; y++) {
            totalDays += isLeapYear(y) ? 366 : 365;
        }
        
        // Add days for the months in the current year
        for (int m = 1; m < month; m++) {
            totalDays += monthDays[m - 1];
            if (m == 2 && isLeapYear(year)) {
                totalDays += 1; // Add leap day for February
            }
        }
        
        // Add days in the current month
        totalDays += day - 1; // Subtract 1 because we start counting from day 0
        
        // January 1, 1971 was a Friday, which is index 5 in the days array
        int dayOfWeekIndex = (totalDays + 5) % 7;
        
        return days[dayOfWeekIndex];            
    }
}
