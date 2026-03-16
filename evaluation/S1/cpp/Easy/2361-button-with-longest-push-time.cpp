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
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
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
        int maxTime = events[0][1];
        int resultIndex = events[0][0];
        
        for (size_t i = 1; i < events.size(); ++i) {
            int currentTime = events[i][1] - events[i - 1][1];
            if (currentTime > maxTime || (currentTime == maxTime && events[i][0] < resultIndex)) {
                maxTime = currentTime;
                resultIndex = events[i][0];
            }
        }
        
        return resultIndex;         
    }
};
