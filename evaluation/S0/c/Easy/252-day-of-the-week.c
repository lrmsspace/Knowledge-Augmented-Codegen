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

char* dayOfTheWeek(int day, int month, int year) {
    // Array to store the number of days in each month
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Array to store the names of the days of the week
    char* days_of_week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    // Calculate the total number of days from 1971-01-01 to the given date
    int total_days = 0;
    
    // Add days for the years from 1971 to year-1
    for (int y = 1971; y < year; y++) {
        total_days += 365;
        // Check for leap year
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
            total_days += 1;
        }
    }
    
    // Add days for the months in the current year
    for (int m = 1; m < month; m++) {
        total_days += days_in_month[m - 1];
        // Check for leap year in February
        if (m == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
            total_days += 1;
        }
    }
    
    // Add the days in the current month
    total_days += day - 1; // Subtracting 1 because we start counting from day 0
    
    // January 1, 1971 was a Friday, which is index 5 in days_of_week
    int day_index = (total_days + 5) % 7;
    
    return days_of_week[day_index];     
}
