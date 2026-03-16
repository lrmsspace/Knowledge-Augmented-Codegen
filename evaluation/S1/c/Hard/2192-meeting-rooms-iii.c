// Source: https://leetcode.com/problems/meeting-rooms-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. There are n rooms numbered from 0 to n - 1.
//
// You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.
//
// Meetings are allocated to rooms in the following manner:
//
//
// 	Each meeting will take place in the unused room with the lowest number.
// 	If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
// 	When a room becomes unused, meetings that have an earlier original start time should be given the room.
//
//
// Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.
//
// A half-closed interval [a, b) is the interval between a and b including a and not including b.
//
// Example:
// Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
// Output: 0
// Explanation:
// - At time 0, both rooms are not being used. The first meeting starts in room 0.
// - At time 1, only room 1 is not being used. The second meeting starts in room 1.
// - At time 2, both rooms are being used. The third meeting is delayed.
// - At time 3, both rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
// - At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
// Both rooms 0 and 1 held 2 meetings, so we return 0.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= meetings.length <= 105
// 	meetings[i].length == 2
// 	0 <= starti < endi <= 5 * 105
// 	All the values of starti are unique.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    // Event structure
    typedef struct {
        int time;
        int type; // 0 = start, 1 = end
        int room;
    } Event;

    // Compare function for qsort
    int cmpEvent(const void* a, const void* b) {
        Event* ea = (Event*)a;
        Event* eb = (Event*)b;
        if (ea->time != eb->time) return ea->time - eb->time;
        return ea->type - eb->type; // end events before start events
    }

    // Create events
    Event* events = (Event*)malloc(2 * meetingsSize * sizeof(Event));
    for (int i = 0; i < meetingsSize; i++) {
        events[2 * i] = (Event){meetings[i][0], 0, -1}; // start event
        events[2 * i + 1] = (Event){meetings[i][1], 1, -1}; // end event
    }

    // Sort events by time
    qsort(events, 2 * meetingsSize, sizeof(Event), cmpEvent);

    // Room availability and meeting counts
    int* roomAvailable = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) roomAvailable[i] = 0; // all rooms available at time 0
    int* meetingCount = (int*)calloc(n, sizeof(int));

    // Process events
    for (int i = 0; i < 2 * meetingsSize; i++) {
        Event e = events[i];
        if (e.type == 0) { // start event
            // Find the lowest numbered available room
            int room = -1;
            for (int r = 0; r < n; r++) {
                if (roomAvailable[r] <= e.time) {
                    room = r;
                    break;
                }
            }
            if (room != -1) {
                // Assign room and increment meeting count
                roomAvailable[room] = e.time + (meetings[i / 2][1] - meetings[i / 2][0]);
                meetingCount[room]++;
            } else {
                // All rooms busy, delay meeting
                int earliestRoom = 0;
                for (int r = 1; r < n; r++) {
                    if (roomAvailable[r] < roomAvailable[earliestRoom]) {
                        earliestRoom = r;
                    }
                }
                // Delay meeting to when the earliest room is free
                int delay = roomAvailable[earliestRoom] - e.time;
                roomAvailable[earliestRoom] += (meetings[i / 2][1] - meetings[i / 2][0]);
                meetingCount[earliestRoom]++;
            }
        }
    }
    // Find the room with the maximum meetings
    int maxMeetings = 0;    
    int resultRoom = 0;
    for (int r = 0; r < n; r++) {
        if (meetingCount[r] > maxMeetings) {
            maxMeetings = meetingCount[r];
            resultRoom = r;
        }
    }
    free(events);
    free(roomAvailable);
    free(meetingCount);
    return resultRoom;    
}
