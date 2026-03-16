// Source: https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.
//
// Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.
//
// Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.
//
// Example:
// Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
//
// Output: [2,3]
//
// Explanation:
//
// You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.
//
// Constraints:
// 1 <= intevals.length <= 5 * 104
// 	intervals[i].length == 3
// 	intervals[i] = [li, ri, weighti]
// 	1 <= li <= ri <= 109
// 	1 <= weighti <= 109
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumWeight(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize) {
    /* Sort intervals by starting time */
    int cmp(const void *a, const void *b) {
        int *ia = *(int **)a;
        int *ib = *(int **)b;
        if (ia[0] != ib[0]) return ia[0] - ib[0];
        if (ia[1] != ib[1]) return ia[1] - ib[1];
        return ia[2] - ib[2];
    }
    qsort(intervals, intervalsSize, sizeof(int*), cmp);

    /* DP array to store maximum weight and chosen indices */
    typedef struct {
        long long weight;
        int indices[4];
        int count;
    } DPState;

    DPState dp[intervalsSize + 1];
    for (int i = 0; i <= intervalsSize; ++i) {
        dp[i].weight = 0;
        dp[i].count = 0;
    }

    for (int i = 1; i <= intervalsSize; ++i) {
        int l = intervals[i - 1][0];
        int r = intervals[i - 1][1];
        int w = intervals[i - 1][2];

        /* Find the last non-overlapping interval */
        int j = i - 1;
        while (j > 0 && intervals[j - 1][1] >= l) {
            --j;
        }

        /* Option 1: Do not take the current interval */
        dp[i] = dp[i - 1];

        /* Option 2: Take the current interval */
        if (dp[j].count < 4) {
            long long newWeight = dp[j].weight + w;
            if (newWeight > dp[i].weight ||
                (newWeight == dp[i].weight && 
                 (dp[j].count + 1 < dp[i].count || 
                  (dp[j].count + 1 == dp[i].count && 
                   memcmp(dp[j].indices, dp[i].indices, dp[j].count * sizeof(int)) < 0)))) {
                dp[i].weight = newWeight;
                memcpy(dp[i].indices, dp[j].indices, dp[j].count * sizeof(int));
                dp[i].indices[dp[j].count] = i - 1;
                dp[i].count = dp[j].count + 1;
            }
        }
    }
    /* Prepare result */
    int *result = (int*)malloc(dp[intervalsSize].count * sizeof(int));
    *returnSize = dp[intervalsSize].count;
    for (int i = 0; i < dp[intervalsSize].count; ++i) {
        result[i] = dp[intervalsSize].indices[i];
    }
    return result;
}
