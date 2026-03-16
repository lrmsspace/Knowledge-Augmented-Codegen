// Source: https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array ranges where ranges[i] = [starti, endi] denotes that all integers between starti and endi (both inclusive) are contained in the ith range.
//
// You are to split ranges into two (possibly empty) groups such that:
//
//
// 	Each range belongs to exactly one group.
// 	Any two overlapping ranges must belong to the same group.
//
//
// Two ranges are said to be overlapping if there exists at least one integer that is present in both ranges.
//
//
// 	For example, [1, 3] and [2, 5] are overlapping because 2 and 3 occur in both ranges.
//
//
// Return the total number of ways to split ranges into two groups. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: ranges = [[6,10],[5,15]]
// Output: 2
// Explanation: 
// The two ranges are overlapping, so they must be in the same group.
// Thus, there are two possible ways:
// - Put both the ranges together in group 1.
// - Put both the ranges together in group 2.
//
// Constraints:
// 1 <= ranges.length <= 105
// 	ranges[i].length == 2
// 	0 <= starti <= endi <= 109
//
// Helpful references (internal KB):
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
//   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
//   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
//   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
//   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
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

int countWays(int** ranges, int rangesSize, int* rangesColSize) {
    // Step 1: Sort the ranges by their start time
    qsort(ranges, rangesSize, sizeof(int*), compare);

    // Step 2: Merge overlapping ranges and count the number of groups
    int groups = 0;
    int currentEnd = -1;

    for (int i = 0; i < rangesSize; i++) {
        if (ranges[i][0] > currentEnd) {
            // Start of a new group
            groups++;
            currentEnd = ranges[i][1];
        } else {
            // Update the end of the current group if needed
            if (ranges[i][1] > currentEnd) {
                currentEnd = ranges[i][1];
            }
        }
    }

    // Step 3: Calculate the number of ways to split into two groups
    long long result = 1;
    for (int i = 0; i < groups; i++) {
        result = (result * 2) % 1000000007;
    }

    return (int)result;     
}
