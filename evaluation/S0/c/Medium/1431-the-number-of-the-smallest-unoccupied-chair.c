// Source: https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/   |   Difficulty: Medium
//
// Problem Description:
// There is a party where n friends numbered from 0 to n - 1 are attending. There is an infinite number of chairs in this party that are numbered from 0 to infinity. When a friend arrives at the party, they sit on the unoccupied chair with the smallest number.
//
//
// 	For example, if chairs 0, 1, and 5 are occupied when a friend comes, they will sit on chair number 2.
//
//
// When a friend leaves the party, their chair becomes unoccupied at the moment they leave. If another friend arrives at that same moment, they can sit in that chair.
//
// You are given a 0-indexed 2D integer array times where times[i] = [arrivali, leavingi], indicating the arrival and leaving times of the ith friend respectively, and an integer targetFriend. All arrival times are distinct.
//
// Return the chair number that the friend numbered targetFriend will sit on.
//
// Example:
// Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
// Output: 1
// Explanation: 
// - Friend 0 arrives at time 1 and sits on chair 0.
// - Friend 1 arrives at time 2 and sits on chair 1.
// - Friend 1 leaves at time 3 and chair 1 becomes empty.
// - Friend 0 leaves at time 4 and chair 0 becomes empty.
// - Friend 2 arrives at time 4 and sits on chair 0.
// Since friend 1 sat on chair 1, we return 1.
//
// Constraints:
// n == times.length
// 	2 <= n <= 104
// 	times[i].length == 2
// 	1 <= arrivali < leavingi <= 105
// 	0 <= targetFriend <= n - 1
// 	Each arrivali time is distinct.
//

int smallestChair(int** times, int timesSize, int* timesColSize, int targetFriend) {
    typedef struct {
        int time;
        int friendIdx;
        int isArrival; // 1 for arrival, 0 for leaving
    } Event;

    int eventCount = timesSize * 2;
    Event* events = (Event*)malloc(eventCount * sizeof(Event));
    for (int i = 0; i < timesSize; i++) {
        events[2 * i] = (Event){times[i][0], i, 1}; // arrival
        events[2 * i + 1] = (Event){times[i][1], i, 0}; // leaving
    }

    // Sort events by time, with arrivals before leavings at the same time
    qsort(events, eventCount, sizeof(Event), [](const void* a, const void* b) {
        Event* ea = (Event*)a;
        Event* eb = (Event*)b;
        if (ea->time != eb->time) return ea->time - eb->time;
        return eb->isArrival - ea->isArrival; // arrivals first
    });

    int* chairOccupied = (int*)calloc(timesSize, sizeof(int)); // chairOccupied[i] = friendIdx or -1 if unoccupied
    for (int i = 0; i < timesSize; i++) chairOccupied[i] = -1;

    int* friendToChair = (int*)malloc(timesSize * sizeof(int)); // friendToChair[friendIdx] = chairIdx
    for (int i = 0; i < timesSize; i++) friendToChair[i] = -1;

    for (int i = 0; i < eventCount; i++) {
        Event event = events[i];
        if (event.isArrival) {
            // Find the smallest unoccupied chair
            for (int chairIdx = 0; chairIdx < timesSize; chairIdx++) {
                if (chairOccupied[chairIdx] == -1) {
                    chairOccupied[chairIdx] = event.friendIdx;
                    friendToChair[event.friendIdx] = chairIdx;
                    if (event.friendIdx == targetFriend) {
                        free(events);
                        free(chairOccupied);
                        free(friendToChair);
                        return chairIdx;
                    }
                    break;
                }
            }
        } else {
            // Friend leaves, free their chair
            int chairIdx = friendToChair[event.friendIdx];
            chairOccupied[chairIdx] = -1;
        }
    }
    free(events);
    free(chairOccupied);
    free(friendToChair);
    return -1; // Should never reach here
}
