// Source: https://leetcode.com/problems/merge-intervals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
//
// Example:
// Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
//
// Constraints:
// 1 <= intervals.length <= 104
// 	intervals[i].length == 2
// 	0 <= starti <= endi <= 104
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Finding intersection of two segments (geometry, interval, simulation, interval-scheduling)
//   • When to use: When determining if two line segments in 2D space cross, touch, or overlap, and to find the nature of their intersection (point, segment, or empty).
//   • Idea: This algorithm determines if two line segments intersect and calculates their intersection point or segment. It typically involves checking for orientation changes and handling special cases like collinearity, with an O(1) time complexity.
//   • Invariants: The bounding boxes of the two segments must overlap for an intersection to be possible.; If segments are collinear, their intersection is either empty, a point, or a sub-segment.
//   • Tips: Use a bounding box check first for early exit optimization.; Handle collinear segments as a distinct special case.
//   • Pitfalls: Incorrectly handling parallel or perfectly collinear segments.; Floating point inaccuracies leading to false positives or negatives.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} intervals
 * @return {number[][]}
 */
var merge = function(intervals) {
    if (intervals.length === 0) {
        return [];
    }

    intervals.sort((a, b) => a[0] - b[0]);

    const merged = [];
    let currentInterval = intervals[0];

    for (const interval of intervals) {
        if (interval[0] <= currentInterval[1]) {
            currentInterval[1] = Math.max(currentInterval[1], interval[1]);
        } else {
            merged.push(currentInterval);
            currentInterval = interval;
        }
    }

    merged.push(currentInterval);

    return merged;
};
