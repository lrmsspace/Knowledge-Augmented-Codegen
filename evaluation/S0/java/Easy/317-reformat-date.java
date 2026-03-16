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

class Solution {
    public String reformatDate(String date) {
        String[] months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        String[] parts = date.split(" ");
        
        String dayPart = parts[0];
        String monthPart = parts[1];
        String yearPart = parts[2];
        
        // Extract day number and format it to two digits
        String dayNumber = dayPart.substring(0, dayPart.length() - 2);
        if (dayNumber.length() == 1) {
            dayNumber = "0" + dayNumber;
        }
        
        // Find month number
        String monthNumber = "";
        for (int i = 0; i < months.length; i++) {
            if (months[i].equals(monthPart)) {
                monthNumber = String.format("%02d", i + 1);
                break;
            }
        }
        
        // Construct the final date string in YYYY-MM-DD format
        return yearPart + "-" + monthNumber + "-" + dayNumber;          
    }
}
