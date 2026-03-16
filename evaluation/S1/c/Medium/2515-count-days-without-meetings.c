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
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countDays(int days, int** meetings, int meetingsSize, int* meetingsColSize) {
    // Create an array to hold the event points
    int eventCount = meetingsSize * 2;
    int (*events)[2] = malloc(eventCount * sizeof(*events));
    if (!events) return -1; // Handle memory allocation failure

    // Populate the event points
    for (int i = 0; i < meetingsSize; i++) {
        events[i * 2][0] = meetings[i][0];
        events[i * 2][1] = 1; // Start of a meeting
        events[i * 2 + 1][0] = meetings[i][1] + 1;
        events[i * 2 + 1][1] = -1; // End of a meeting
    }

    // Sort the event points
    qsort(events, eventCount, sizeof(*events), [](const void* a, const void* b) {
        int* ea = (int*)a;
        int* eb = (int*)b;
        if (ea[0] != eb[0]) return ea[0] - eb[0];
        return ea[1] - eb[1];
    });

    // Sweep line algorithm to count busy days
    int busyDays = 0;
    int activeMeetings = 0;
    int prevDay = 1;

    for (int i = 0; i < eventCount; i++) {
        int currentDay = events[i][0];
        if (activeMeetings > 0) {
            busyDays += currentDay - prevDay;
        }
        activeMeetings += events[i][1];
        prevDay = currentDay;
    }

    // Calculate free days
    int freeDays = days - busyDays;

    // Free allocated memory
    free(events);

    return freeDays;        
}
