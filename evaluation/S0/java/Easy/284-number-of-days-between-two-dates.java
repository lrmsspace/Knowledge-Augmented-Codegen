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
    public int daysBetweenDates(String date1, String date2) {
        return Math.abs(toDays(date1) - toDays(date2));         
    }
}
