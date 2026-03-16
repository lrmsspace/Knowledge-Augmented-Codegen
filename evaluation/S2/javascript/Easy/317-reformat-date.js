// Source: https://leetcode.com/problems/reformat-date/   |   Difficulty: Easy
//
// Problem Description:
// Given a date string in the form Day Month Year, where:
//
//
// 	Day is in the set {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}.
// 	Month is in the set {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}.
// 	Year is in the range [1900, 2100].
//
//
// Convert the date string to the format YYYY-MM-DD, where:
//
//
// 	YYYY denotes the 4 digit year.
// 	MM denotes the 2 digit month.
// 	DD denotes the 2 digit day.
//
// Example:
// Input: date = "20th Oct 2052"
// Output: "2052-10-20"
//
// Constraints:
// The given dates are guaranteed to be valid, so no error handling is necessary.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} date
 * @return {string}
 */
var reformatDate = function(date) {
    const [day, month, year] = date.split(' ');
    const monthMap = {
        'Jan': '01',
        'Feb': '02',
        'Mar': '03',
        'Apr': '04',
        'May': '05',
        'Jun': '06',
        'Jul': '07',
        'Aug': '08',
        'Sep': '09',
        'Oct': '10',
        'Nov': '11',
        'Dec': '12'
    };
    
    // Extract the numeric part of the day (e.g., "20th" -> "20")
    const dayNumber = parseInt(day.replace(/[^0-9]/g, ''), 10);
    
    // Format day to two digits
    const formattedDay = dayNumber.toString().padStart(2, '0');
    
    // Return the reformatted date
    return `${year}-${monthMap[month]}-${formattedDay}`;

 };
