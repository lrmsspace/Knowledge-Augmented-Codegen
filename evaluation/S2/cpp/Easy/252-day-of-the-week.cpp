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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        // Zeller's Congruence algorithm to calculate the day of the week
        static const vector<string> daysOfWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        
        if (month < 3) {
            month += 12;
            year -= 1;
        }
        
        int k = year % 100; // Year of the century
        int j = year / 100; // Zero-based century
        
        int f = day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j);
        int dayOfWeekIndex = ((f % 7) + 7) % 7; // Ensure non-negative index
        
        return daysOfWeek[dayOfWeekIndex];          
    }
};
