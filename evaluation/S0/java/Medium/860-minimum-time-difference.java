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

class Solution {
    public int findMinDifference(List<String> timePoints) {
        boolean[] mark = new boolean[1440];
        for (String time : timePoints) {
            String[] t = time.split(":");
            int minutes = Integer.parseInt(t[0]) * 60 + Integer.parseInt(t[1]);
            if (mark[minutes]) {
                return 0;
            }
            mark[minutes] = true;
        }

        int prev = -1, first = -1, minDiff = Integer.MAX_VALUE;
        for (int i = 0; i < 1440; i++) {
            if (mark[i]) {
                if (prev != -1) {
                    minDiff = Math.min(minDiff, i - prev);
                } else {
                    first = i;
                }
                prev = i;
            }
        }
        minDiff = Math.min(minDiff, (first + 1440) - prev);
        return minDiff;         
    }
}
