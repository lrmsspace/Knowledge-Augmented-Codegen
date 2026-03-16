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

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());

        long long busyDays = 0;
        long long currentStart = -1;
        long long currentEnd = -1;

        for (const auto& meeting : meetings) {
            if (meeting[0] > currentEnd) {
                // No overlap with the current busy period
                if (currentStart != -1) {
                    busyDays += (currentEnd - currentStart + 1);
                }
                currentStart = meeting[0];
                currentEnd = meeting[1];
            } else {
                // Overlap, extend the current busy period if needed
                currentEnd = max(currentEnd, (long long)meeting[1]);
            }
        }

        // Add the last busy period
        if (currentStart != -1) {
            busyDays += (currentEnd - currentStart + 1);
        }

        return days - busyDays;         
    }
};
