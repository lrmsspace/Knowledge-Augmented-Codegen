// Source: https://leetcode.com/problems/video-stitching/   |   Difficulty: Medium
//
// Problem Description:
// You are given a series of video clips from a sporting event that lasted time seconds. These video clips can be overlapping with each other and have varying lengths.
//
// Each video clip is described by an array clips where clips[i] = [starti, endi] indicates that the ith clip started at starti and ended at endi.
//
// We can cut these clips into segments freely.
//
//
// 	For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
//
//
// Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event [0, time]. If the task is impossible, return -1.
//
// Example:
// Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
// Output: 3
// Explanation: We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
// Then, we can reconstruct the sporting event as follows:
// We cut [1,9] into segments [1,2] + [2,8] + [8,9].
// Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
//
// Constraints:
// 1 <= clips.length <= 100
// 	0 <= starti <= endi <= 100
// 	1 <= time <= 100
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Range Minimum Query (array, ds, divide-and-conquer)
//   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
//   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
//   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
//   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int videoStitching(int** clips, int clipsSize, int* clipsColSize, int time) {
    int maxEnd[101] = {0};
    for (int i = 0; i < clipsSize; i++) {
        int start = clips[i][0];
        int end = clips[i][1];
        if (end > maxEnd[start]) {
            maxEnd[start] = end;
        }
    }

    int lastEnd = 0;
    int ret = 0;
    int i = 0;

    while (i < time) {
        int farthest = lastEnd;
        for (; i <= lastEnd; i++) {
            if (maxEnd[i] > farthest) {
                farthest = maxEnd[i];
            }
        }
        if (farthest == lastEnd) {
            return -1;
        }
        ret++;
        lastEnd = farthest;
    }

    return ret;     
}
