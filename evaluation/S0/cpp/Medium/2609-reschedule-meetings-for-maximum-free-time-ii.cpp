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
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();
        vector<int> freeTimes(n + 1);
        freeTimes[0] = startTime[0];
        for (int i = 1; i < n; ++i) {
            freeTimes[i] = startTime[i] - endTime[i - 1];
        }
        freeTimes[n] = eventTime - endTime[n - 1];

        int maxFree = *max_element(freeTimes.begin(), freeTimes.end());

        for (int i = 0; i < n; ++i) {
            int duration = endTime[i] - startTime[i];
            int newStart = (i == 0) ? 0 : endTime[i - 1];
            int newEnd = newStart + duration;

            int freeBefore = (i == 0) ? 0 : freeTimes[i - 1];
            int freeAfter = (i == n - 1) ? (eventTime - newEnd) : (startTime[i + 1] - newEnd);

            maxFree = max(maxFree, freeBefore + freeAfter);
        }

        return maxFree;         
    }
};
