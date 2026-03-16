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

/**
 * @param {string} date1
 * @param {string} date2
 * @return {number}
 */
var daysBetweenDates = function(date1, date2) {
    const toDate = (dateStr) => {
        const [year, month, day] = dateStr.split('-').map(Number);
        return new Date(year, month - 1, day);
    };

    const d1 = toDate(date1);
    const d2 = toDate(date2);
    const diffTime = Math.abs(d2 - d1);
    const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));
    return diffDays;
};
