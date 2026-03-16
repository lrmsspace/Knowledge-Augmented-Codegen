// Source: https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array intervals where intervals[i] = [lefti, righti] represents the inclusive interval [lefti, righti].
//
// You have to divide the intervals into one or more groups such that each interval is in exactly one group, and no two intervals that are in the same group intersect each other.
//
// Return the minimum number of groups you need to make.
//
// Two intervals intersect if there is at least one common number between them. For example, the intervals [1, 5] and [5, 8] intersect.
//
// Example:
// Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
// Output: 3
// Explanation: We can divide the intervals into the following groups:
// - Group 1: [1, 5], [6, 8].
// - Group 2: [2, 3], [5, 10].
// - Group 3: [1, 10].
// It can be proven that it is not possible to divide the intervals into fewer than 3 groups.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	intervals[i].length == 2
// 	1 <= lefti <= righti <= 106
//
// Helpful references (internal KB):
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minGroups(int** intervals, int intervalsSize, int* intervalsColSize) {
    // We can use a sweep line algorithm to count the maximum number of overlapping intervals at any point in time.
    // This maximum overlap will give us the minimum number of groups needed.

    // Step 1: Create an array to store the events (start and end of intervals).
    int events[2000002]; // We can have at most 2 * 10^5 events (start and end for each interval).
    int eventCount = 0;

    for (int i = 0; i < intervalsSize; i++) {
        int start = intervals[i][0];
        int end = intervals[i][1];
        events[eventCount++] = start;   // Start of an interval
        events[eventCount++] = -end;    // End of an interval (negative to distinguish from start)
    }

    // Step 2: Sort the events. Start events come before end events if they are the same.
    qsort(events, eventCount, sizeof(int), [](const void* a, const void* b) {
        int valA = *(const int*)a;
        int valB = *(const int*)b;
        if (valA == valB) return 0;
        return (valA > valB) ? 1 : -1; // Ascending order
    });

    // Step 3: Traverse the sorted events and count overlaps.
    int currentOverlap = 0;
    int maxOverlap = 0;

    for (int i = 0; i < eventCount; i++) {
        if (events[i] >= 0) {
            currentOverlap++; // A new interval starts
            if (currentOverlap > maxOverlap) {
                maxOverlap = currentOverlap; // Update max overlap
            }
        } else {
            currentOverlap--; // An interval ends
        }
    }

    return maxOverlap; // The maximum overlap is the minimum number of groups needed        
}
