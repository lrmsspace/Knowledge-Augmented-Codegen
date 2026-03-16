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
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxTwoEvents(int** events, int eventsSize, int* eventsColSize) {
    // Sort events by start time
    int aux[eventsSize][3];
    for (int i = 0; i < eventsSize; i++) {
        aux[i][0] = events[i][0];
        aux[i][1] = events[i][1];
        aux[i][2] = events[i][2];
    }

    // Mergesort implementation
    void merge(int arr[][3], int aux[][3], int lo, int mid, int hi) {
        for (int k = lo; k <= hi; k++) {
            aux[k][0] = arr[k][0];
            aux[k][1] = arr[k][1];
            aux[k][2] = arr[k][2];
        }
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                arr[k][0] = aux[j][0];
                arr[k][1] = aux[j][1];
                arr[k][2] = aux[j][2];
                j++;
            } else if (j > hi) {
                arr[k][0] = aux[i][0];
                arr[k][1] = aux[i][1];
                arr[k][2] = aux[i][2];
                i++;
            } else if (aux[i][0] <= aux[j][0]) {
                arr[k][0] = aux[i][0];
                arr[k][1] = aux[i][1];
                arr[k][2] = aux[i][2];
                i++;
            } else {
                arr[k][0] = aux[j][0];
                arr[k][1] = aux[j][1];
                arr[k][2] = aux[j][2];
                j++;
            }
        }
    }

    void sort(int arr[][3], int aux[][3], int lo, int hi) {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(arr, aux, lo, mid);
        sort(arr, aux, mid + 1, hi);
        merge(arr, aux, lo, mid, hi);
    }

    sort(aux, (int (*)[3])malloc(sizeof(int) * eventsSize * 3), 0, eventsSize - 1);

    // Find the maximum value of non-overlapping events
    int max_value_up_to[eventsSize];
    int max_value = 0;
    for (int i = 0; i < eventsSize; i++) {
        if (i == 0) {
            max_value_up_to[i] = aux[i][2];
        } else {
            if (aux[i][2] > max_value_up_to[i - 1]) {
                max_value_up_to[i] = aux[i][2];
            } else {
                max_value_up_to[i] = max_value_up_to[i - 1];
            }
        }
    }
    int result = 0;
    for (int i = 0; i < eventsSize; i++) {
        // Binary search for the latest event that ends before aux[i][0]
        int left = 0, right = i - 1;
        int best_index = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (aux[mid][1] < aux[i][0]) {
                best_index = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        int current_value = aux[i][2];
        if (best_index != -1) {
            current_value += max_value_up_to[best_index];
        }
        if (current_value > result) {
            result = current_value;
        }
    }
    return result;
}
