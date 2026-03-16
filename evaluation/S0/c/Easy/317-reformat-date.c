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

char* reformatDate(char* date) {
    static const char *months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    
    char *day_str = strtok(date, " ");
    char *month_str = strtok(NULL, " ");
    char *year_str = strtok(NULL, " ");
    
    // Extract day number and format it to two digits
    int day = atoi(day_str);
    char day_formatted[3];
    snprintf(day_formatted, sizeof(day_formatted), "%02d", day);
    
    // Find month number
    int month = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_str, months[i]) == 0) {
            month = i + 1;
            break;
        }
    }
    
    // Format month to two digits
    char month_formatted[3];
    snprintf(month_formatted, sizeof(month_formatted), "%02d", month);
    
    // Allocate memory for the final formatted date string
    char *formatted_date = (char *)malloc(11 * sizeof(char));
    snprintf(formatted_date, 11, "%s-%s-%s", year_str, month_formatted, day_formatted);
    
    return formatted_date;      
}
