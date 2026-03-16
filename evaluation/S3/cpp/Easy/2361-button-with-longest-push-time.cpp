// Source: https://leetcode.com/problems/button-with-longest-push-time/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D array events which represents a sequence of events where a child pushes a series of buttons on a keyboard.
//
// Each events[i] = [indexi, timei] indicates that the button at index indexi was pressed at time timei.
//
//
// 	The array is sorted in increasing order of time.
// 	The time taken to press a button is the difference in time between consecutive button presses. The time for the first button is simply the time at which it was pressed.
//
//
// Return the index of the button that took the longest time to push. If multiple buttons have the same longest time, return the button with the smallest index.
//
// Example:
// Input: events = [[1,2],[2,5],[3,9],[1,15]]
//
// Output: 1
//
// Explanation:
//
//
// 	Button with index 1 is pressed at time 2.
// 	Button with index 2 is pressed at time 5, so it took 5 - 2 = 3 units of time.
// 	Button with index 3 is pressed at time 9, so it took 9 - 5 = 4 units of time.
// 	Button with index 1 is pressed again at time 15, so it took 15 - 9 = 6 units of time.
//
// Constraints:
// 1 <= events.length <= 1000
// 	events[i] == [indexi, timei]
// 	1 <= indexi, timei <= 105
// 	The input is generated such that events is sorted in increasing order of timei.
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int buttonWithLongestTime(vector<vector<int>>& events) {
        int max_time = events[0][1];
        int button_index = events[0][0];
        
        for (size_t i = 1; i < events.size(); ++i) {
            int current_time = events[i][1] - events[i - 1][1];
            if (current_time > max_time || (current_time == max_time && events[i][0] < button_index)) {
                max_time = current_time;
                button_index = events[i][0];
            }
        }
        
        return button_index;            
    }
};
