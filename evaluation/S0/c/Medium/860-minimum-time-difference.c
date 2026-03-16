// Source: https://leetcode.com/problems/minimum-time-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
//
// Example:
// Input: timePoints = ["23:59","00:00"]
// Output: 1
//
// Constraints:
// 2 <= timePoints.length <= 2 * 104
// 	timePoints[i] is in the format "HH:MM".
//

int findMinDifference(char** timePoints, int timePointsSize) {
    int minutes[1440] = {0};
    for (int i = 0; i < timePointsSize; i++) {
        int hour = (timePoints[i][0] - '0') * 10 + (timePoints[i][1] - '0');
        int minute = (timePoints[i][3] - '0') * 10 + (timePoints[i][4] - '0');
        int totalMinutes = hour * 60 + minute;
        if (minutes[totalMinutes] == 1) {
            return 0; // Duplicate time point found
        }
        minutes[totalMinutes] = 1;
    }

    int firstTime = -1;
    int prevTime = -1;
    int minDiff = 1440; // Maximum possible difference in minutes

    for (int i = 0; i < 1440; i++) {
        if (minutes[i] == 1) {
            if (firstTime == -1) {
                firstTime = i;
            }
            if (prevTime != -1) {
                minDiff = (i - prevTime < minDiff) ? (i - prevTime) : minDiff;
            }
            prevTime = i;
        }
    }

    // Check the difference between the last and first time points across midnight
    minDiff = ((firstTime + 1440) - prevTime < minDiff) ? ((firstTime + 1440) - prevTime) : minDiff;

    return minDiff;     
}
