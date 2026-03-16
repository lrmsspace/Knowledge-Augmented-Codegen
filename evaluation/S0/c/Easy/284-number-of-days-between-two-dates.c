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

int daysBetweenDates(char* date1, char* date2) {
    int days_in_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int parse_date(const char* date, int* year, int* month, int* day) {
        sscanf(date, "%d-%d-%d", year, month, day);
        return 0;
    }

    int is_leap_year(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int count_days(int year, int month, int day) {
        int total_days = 0;

        for (int y = 1971; y < year; y++) {
            total_days += is_leap_year(y) ? 366 : 365;
        }

        for (int m = 1; m < month; m++) {
            total_days += days_in_months[m - 1];
            if (m == 2 && is_leap_year(year)) {
                total_days += 1;
            }
        }

        total_days += day;

        return total_days;
    }

    int year1, month1, day1;
    int year2, month2, day2;

    parse_date(date1, &year1, &month1, &day1);
    parse_date(date2, &year2, &month2, &day2);

    int total_days1 = count_days(year1, month1, day1);
    int total_days2 = count_days(year2, month2, day2);

    return abs(total_days1 - total_days2);      
}
