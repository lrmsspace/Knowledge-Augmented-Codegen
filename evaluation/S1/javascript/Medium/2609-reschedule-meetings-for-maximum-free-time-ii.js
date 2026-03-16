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
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} eventTime
 * @param {number[]} startTime
 * @param {number[]} endTime
 * @return {number}
 */
var maxFreeTime = function(eventTime, startTime, endTime) {
     const n = startTime.length;
    let maxFree = 0;

    // Calculate initial free time
    maxFree = Math.max(maxFree, startTime[0]); // Free time before the first meeting
    for (let i = 1; i < n; i++) {
        maxFree = Math.max(maxFree, startTime[i] - endTime[i - 1]); // Free time between meetings
    }
    maxFree = Math.max(maxFree, eventTime - endTime[n - 1]); // Free time after the last meeting

    // Try rescheduling each meeting and calculate the new free time
    for (let i = 0; i < n; i++) {
        const duration = endTime[i] - startTime[i];
        let newStart, newEnd;

        if (i === 0) {
            // Reschedule the first meeting to the end of the event
            newStart = eventTime - duration;
            newEnd = eventTime;
        } else if (i === n - 1) {
            // Reschedule the last meeting to the beginning of the event
            newStart = 0;
            newEnd = duration;
        } else {
            // Reschedule the meeting to fit between endTime[i-1] and startTime[i+1]
            const prevEnd = endTime[i - 1];
            const nextStart = startTime[i + 1];
            if (prevEnd + duration <= nextStart) {
                newStart = prevEnd;
                newEnd = prevEnd + duration;
            } else {
                continue; // Cannot reschedule this meeting without overlap
            }
        }

        // Calculate free time after rescheduling
        let currentMaxFree = 0;
        currentMaxFree = Math.max(currentMaxFree, newStart); // Free time before the rescheduled meeting
        for (let j = 0; j < n; j++) {
            if (j === i) continue; // Skip the rescheduled meeting
            const currentStart = j < i ? startTime[j] : (j > i ? startTime[j] : newStart);
            const currentEnd = j < i ? endTime[j] : (j > i ? endTime[j] : newEnd);
            if (currentStart > newEnd) {
                currentMaxFree = Math.max(currentMaxFree, currentStart - newEnd); //
            } else if (currentEnd < newStart) {
                currentMaxFree = Math.max(currentMaxFree, newStart - currentEnd); // Free time after the rescheduled meeting
            }
        }
        currentMaxFree = Math.max(currentMaxFree, eventTime - newEnd); // Free time after the last meeting
        maxFree = Math.max(maxFree, currentMaxFree);
    }
    return maxFree;
};
