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
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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
    int hardestWorker(int n, vector<vector<int>>& logs) {
        int maxTime = 0;
        int employeeId = 0;
        int prevTime = 0;

        for (const auto& log : logs) {
            int id = log[0];
            int leaveTime = log[1];
            int taskTime = leaveTime - prevTime;

            if (taskTime > maxTime || (taskTime == maxTime && id < employeeId)) {
                maxTime = taskTime;
                employeeId = id;
            }

            prevTime = leaveTime;
        }

        return employeeId;          
    }
};
