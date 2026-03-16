// Source: https://leetcode.com/problems/the-employee-that-worked-on-the-longest-task/   |   Difficulty: Easy
//
// Problem Description:
// There are n employees, each with a unique id from 0 to n - 1.
//
// You are given a 2D integer array logs where logs[i] = [idi, leaveTimei] where:
//
//
// 	idi is the id of the employee that worked on the ith task, and
// 	leaveTimei is the time at which the employee finished the ith task. All the values leaveTimei are unique.
//
//
// Note that the ith task starts the moment right after the (i - 1)th task ends, and the 0th task starts at time 0.
//
// Return the id of the employee that worked the task with the longest time. If there is a tie between two or more employees, return the smallest id among them.
//
// Example:
// Input: n = 10, logs = [[0,3],[2,5],[0,9],[1,15]]
// Output: 1
// Explanation: 
// Task 0 started at 0 and ended at 3 with 3 units of times.
// Task 1 started at 3 and ended at 5 with 2 units of times.
// Task 2 started at 5 and ended at 9 with 4 units of times.
// Task 3 started at 9 and ended at 15 with 6 units of times.
// The task with the longest time is task 3 and the employee with id 1 is the one that worked on it, so we return 1.
//
// Constraints:
// 2 <= n <= 500
// 	1 <= logs.length <= 500
// 	logs[i].length == 2
// 	0 <= idi <= n - 1
// 	1 <= leaveTimei <= 500
// 	idi != idi+1
// 	leaveTimei are sorted in a strictly increasing order.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int hardestWorker(int n, vector<vector<int>>& logs) {
        int max_time = 0;
        int employee_id = 0;
        int prev_time = 0;

        for (const auto& log : logs) {
            int id = log[0];
            int leave_time = log[1];
            int task_time = leave_time - prev_time;

            if (task_time > max_time || (task_time == max_time && id < employee_id)) {
                max_time = task_time;
                employee_id = id;
            }

            prev_time = leave_time;
        }

        return employee_id;         
    }
};
