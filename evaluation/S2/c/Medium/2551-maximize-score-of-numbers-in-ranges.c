// Source: https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers start and an integer d, representing n intervals [start[i], start[i] + d].
//
// You are asked to choose n integers where the ith integer must belong to the ith interval. The score of the chosen integers is defined as the minimum absolute difference between any two integers that have been chosen.
//
// Return the maximum possible score of the chosen integers.
//
// Example:
// Input: start = [6,0,3], d = 2
//
// Output: 4
//
// Explanation:
//
// The maximum possible score can be obtained by choosing integers: 8, 0, and 4. The score of these chosen integers is min(|8 - 0|, |8 - 4|, |0 - 4|) which equals 4.
//
// Constraints:
// 2 <= start.length <= 105
// 	0 <= start[i] <= 109
// 	0 <= d <= 109
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxPossibleScore(int* start, int startSize, int d) {
    // Sort the start array to ensure we are working with ordered intervals
    qsort(start, startSize, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // The maximum score is determined by the smallest gap between the chosen integers
    // Since we want to maximize this gap, we can choose integers at the ends of the intervals
    // The best choice is to pick the integer at the end of the first interval and the integer at the start of the last interval
    int maxScore = 0;
    
    for (int i = 0; i < startSize - 1; i++) {
        // Calculate the gap between the end of the current interval and the start of the next interval
        int gap = (start[i] + d) - start[i + 1];
        if (gap > maxScore) {
            maxScore = gap;
        }
    }

    return maxScore;        
}
