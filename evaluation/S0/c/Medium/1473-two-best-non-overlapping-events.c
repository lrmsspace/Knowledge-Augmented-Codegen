// Source: https://leetcode.com/problems/two-best-non-overlapping-events/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.
//
// Return this maximum sum.
//
// Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.
//
// Example:
// Input: events = [[1,3,2],[4,5,2],[2,4,3]]
// Output: 4
// Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
//
// Constraints:
// 2 <= events.length <= 105
// 	events[i].length == 3
// 	1 <= startTimei <= endTimei <= 109
// 	1 <= valuei <= 106
//

int maxTwoEvents(int** events, int eventsSize, int* eventsColSize) {
    // Sort events by start time
    qsort(events, eventsSize, sizeof(int*), [](const void* a, const void* b) {
        return (*(int**)a)[0] - (*(int**)b)[0];
    });

    // Create an array to store the maximum value from the right
    int* maxFromRight = (int*)malloc(eventsSize * sizeof(int));
    maxFromRight[eventsSize - 1] = events[eventsSize - 1][2];

    for (int i = eventsSize - 2; i >= 0; i--) {
        maxFromRight[i] = fmax(maxFromRight[i + 1], events[i][2]);
    }

    int maxSum = 0;

    for (int i = 0; i < eventsSize; i++) {
        int endTime = events[i][1];
        int left = i + 1;
        int right = eventsSize - 1;
        int nextEventIndex = -1;

        // Binary search to find the next non-overlapping event
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (events[mid][0] > endTime) {
                nextEventIndex = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (nextEventIndex != -1) {
            maxSum = fmax(maxSum, events[i][2] + maxFromRight[nextEventIndex]);
        } else {
            maxSum = fmax(maxSum, events[i][2]);
        }
    }

    free(maxFromRight);
    return maxSum;      
}
