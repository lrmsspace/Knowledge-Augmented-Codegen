// Source: https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer eventTime denoting the duration of an event, where the event occurs from time t = 0 to time t = eventTime.
//
// You are also given two integer arrays startTime and endTime, each of length n. These represent the start and end time of n non-overlapping meetings, where the ith meeting occurs during the time [startTime[i], endTime[i]].
//
// You can reschedule at most k meetings by moving their start time while maintaining the same duration, to maximize the longest continuous period of free time during the event.
//
// The relative order of all the meetings should stay the same and they should remain non-overlapping.
//
// Return the maximum amount of free time possible after rearranging the meetings.
//
// Note that the meetings can not be rescheduled to a time outside the event.
//
// Example:
// Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]
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
// 	1 <= k <= n
// 	0 <= startTime[i] < endTime[i] <= eventTime
// 	endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
//

int maxFreeTime(int eventTime, int k, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int n = startTimeSize;
    long long* prefixFree = (long long*)calloc(n + 1, sizeof(long long));
    for (int i = 1; i <= n; i++) {
        prefixFree[i] = prefixFree[i - 1] + (long long)(startTime[i - 1] - (i == 1 ? 0 : endTime[i - 2]));
    }

    long long maxFree = 0;
    for (int i = 0; i <= n - k; i++) {
        long long freeBefore = prefixFree[i];
        long long freeAfter = prefixFree[n] - prefixFree[i + k];
        long long totalFree = freeBefore + freeAfter;

        long long startOfRescheduled = (i == 0 ? 0 : endTime[i - 1]);
        long long endOfRescheduled = (i + k - 1 >= n ? eventTime : startTime[i + k]);

        totalFree += (endOfRescheduled - startOfRescheduled);

        if (totalFree > maxFree) {
            maxFree = totalFree;
        }
    }

    free(prefixFree);
    return (int)maxFree;        
}
