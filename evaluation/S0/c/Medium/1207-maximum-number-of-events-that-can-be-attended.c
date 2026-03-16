// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
//
// You can attend an event i at any day d where startDayi <= d <= endDayi. You can only attend one event at any time d.
//
// Return the maximum number of events you can attend.
//
// Example:
// Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
// Explanation: You can attend all the three events.
// One way to attend them all is as shown.
// Attend the first event on day 1.
// Attend the second event on day 2.
// Attend the third event on day 3.
//
// Constraints:
// 1 <= events.length <= 105
// 	events[i].length == 2
// 	1 <= startDayi <= endDayi <= 105
//

int maxEvents(int** events, int eventsSize, int* eventsColSize) {
    // Sort events by their end days
    int cmp(const void* a, const void* b) {
        return ((int*)a)[1] - ((int*)b)[1];
    }
    qsort(events, eventsSize, sizeof(int*), cmp);

    int maxDay = 0;
    for (int i = 0; i < eventsSize; i++) {
        if (events[i][1] > maxDay) {
            maxDay = events[i][1];
        }
    }

    int* attendedDays = (int*)calloc(maxDay + 1, sizeof(int));
    int count = 0;

    for (int i = 0; i < eventsSize; i++) {
        for (int day = events[i][0]; day <= events[i][1]; day++) {
            if (!attendedDays[day]) {
                attendedDays[day] = 1;
                count++;
                break;
            }
        }
    }

    free(attendedDays);
    return count;       
}
