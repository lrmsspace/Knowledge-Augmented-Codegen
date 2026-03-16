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
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
        int max_time = events[0][1]; // Time for the first button press
        int button_index = events[0][0]; // Index of the first button

        for (size_t i = 1; i < events.size(); ++i) {
            int current_time = events[i][1] - events[i - 1][1]; // Time difference between current and previous press
            if (current_time > max_time) {
                max_time = current_time;
                button_index = events[i][0];
            } else if (current_time == max_time && events[i][0] < button_index) {
                button_index = events[i][0]; // Update to smaller index if time is the same
            }
        }

        return button_index;            
    }
};
