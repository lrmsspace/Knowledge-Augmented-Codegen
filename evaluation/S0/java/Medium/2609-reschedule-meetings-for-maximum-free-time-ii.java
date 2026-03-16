// Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer eventTime denoting the duration of an event. You are also given two integer arrays startTime and endTime, each of length n.
//
// These represent the start and end times of n non-overlapping meetings that occur during the event between time t = 0 and time t = eventTime, where the ith meeting occurs during the time [startTime[i], endTime[i]].
//
// You can reschedule at most one meeting by moving its start time while maintaining the same duration, such that the meetings remain non-overlapping, to maximize the longest continuous period of free time during the event.
//
// Return the maximum amount of free time possible after rearranging the meetings.
//
// Note that the meetings can not be rescheduled to a time outside the event and they should remain non-overlapping.
//
// Note: In this version, it is valid for the relative ordering of the meetings to change after rescheduling one meeting.
//
// Example:
// Input: eventTime = 5, startTime = [1,3], endTime = [2,5]
//
// Output: 2
//
// Explanation:
//
//
//
// Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].
//
// Constraints:
// 1 <= eventTime <= 109
// 	n == startTime.length == endTime.length
// 	2 <= n <= 105
// 	0 <= startTime[i] < endTime[i] <= eventTime
// 	endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
//

class Solution {
    public int maxFreeTime(int eventTime, int[] startTime, int[] endTime) {
        int n = startTime.length;
        int maxFree = Math.max(startTime[0], eventTime - endTime[n - 1]);

        for (int i = 1; i < n; i++) {
            maxFree = Math.max(maxFree, startTime[i] - endTime[i - 1]);
        }

        for (int i = 0; i < n; i++) {
            int meetingDuration = endTime[i] - startTime[i];

            // Try to move the meeting to the beginning
            if (i == 0) {
                int newEnd = startTime[0] + meetingDuration;
                int freeTime = eventTime - newEnd;
                if (n > 1) {
                    freeTime = Math.max(freeTime, startTime[1] - newEnd);
                }
                maxFree = Math.max(maxFree, freeTime);
            }
            // Try to move the meeting to the end
            else if (i == n - 1) {
                int newStart = eventTime - meetingDuration;
                int freeTime = newStart;
                if (n > 1) {
                    freeTime = Math.max(freeTime, newStart - endTime[n - 2]);
                }
                maxFree = Math.max(maxFree, freeTime);
            }
            // Try to move the meeting between other meetings
            else {
                int prevEnd = endTime[i - 1];
                int nextStart = startTime[i + 1];

                // Move meeting right after previous meeting
                int newStart1 = prevEnd;
                int newEnd1 = newStart1 + meetingDuration;
                if (newEnd1 <= nextStart) {
                    int freeTime1 = nextStart - newEnd1;
                    maxFree = Math.max(maxFree, freeTime1);
                }

                // Move meeting right before next meeting
                int newEnd2 = nextStart;
                int newStart2 = newEnd2 - meetingDuration;
                if (newStart2 >= prevEnd) {
                    int freeTime2 = newStart2 - prevEnd;
                    maxFree = Math.max(maxFree, freeTime2);
                }
            }
        }

        return maxFree;         
    }
}
