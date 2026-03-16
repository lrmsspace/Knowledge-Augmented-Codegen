// Source: https://leetcode.com/problems/count-days-without-meetings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer days representing the total number of days an employee is available for work (starting from day 1). You are also given a 2D array meetings of size n where, meetings[i] = [start_i, end_i] represents the starting and ending days of meeting i (inclusive).
//
// Return the count of days when the employee is available for work but no meetings are scheduled.
//
// Note: The meetings may overlap.
//
// Example:
// Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
//
// Output: 2
//
// Explanation:
//
// There is no meeting scheduled on the 4th and 8th days.
//
// Constraints:
// 1 <= days <= 109
// 	1 <= meetings.length <= 105
// 	meetings[i].length == 2
// 	1 <= meetings[i][0] <= meetings[i][1] <= days
//

int countDays(int days, int** meetings, int meetingsSize, int* meetingsColSize) {
    // Create an array to mark meeting days
    char* meetingDays = (char*)calloc(days + 1, sizeof(char));
    if (!meetingDays) {
        return -1; // Memory allocation failed
    }

    // Mark the days with meetings
    for (int i = 0; i < meetingsSize; i++) {
        int start = meetings[i][0];
        int end = meetings[i][1];
        for (int j = start; j <= end; j++) {
            meetingDays[j] = 1; // Mark as meeting day
        }
    }

    // Count the days without meetings
    int count = 0;
    for (int i = 1; i <= days; i++) {
        if (meetingDays[i] == 0) {
            count++;
        }
    }

    // Free allocated memory
    free(meetingDays);

    return count;       
}
