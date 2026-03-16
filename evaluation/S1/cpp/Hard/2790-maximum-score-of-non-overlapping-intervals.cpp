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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> idxs(n);
        for (int i = 0; i < n; ++i) {
            idxs[i] = i;
        }
        sort(idxs.begin(), idxs.end(), [&](int a, int b) {
            return intervals[a][1] < intervals[b][1];
        });

        // dp[i][j]: max weight using first i intervals with j intervals chosen
        vector<vector<long long>> dp(n + 1, vector<long long>(5, 0));
        vector<vector<int>> choice(n + 1, vector<int>(5, -1));

        for (int i = 1; i <= n; ++i) {
            int curIdx = idxs[i - 1];
            int l = intervals[curIdx][0];
            int r = intervals[curIdx][1];
            int w = intervals[curIdx][2];

            // Find the last non-overlapping interval
            int lastNonOverlap = -1;
            for (int j = i - 1; j >= 1; --j) {
                int prevIdx = idxs[j - 1];
                if (intervals[prevIdx][1] < l) {
                    lastNonOverlap = j - 1;
                    break;
                }
            }

            for (int j = 0; j <= 4; ++j) {
                // Not take current interval
                if (dp[i - 1][j] > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j];
                    choice[i][j] = choice[i - 1][j];
                }

                // Take current interval
                if (j > 0) {
                    long long candidate = w;
                    if (lastNonOverlap != -1) {
                        candidate += dp[lastNonOverlap + 1][j - 1];
                    }
                    if (candidate > dp[i][j]) {
                        dp[i][j] = candidate;
                        choice[i][j] = curIdx;
                    }
                }
            }
        }

        // Find the maximum weight and reconstruct the chosen intervals
        long long maxWeight = 0;
        int bestCount = 0;
        for (int j = 0; j <= 4; ++j) {
            if (dp[n][j] > maxWeight) {
                maxWeight = dp[n][j];
                bestCount = j;
            }
        }
        vector<int> result;
        for (int i = n, j = bestCount; i > 0 && j > 0; --i) {
            if (choice[i][j] != -1) {
                result.push_back(choice[i][j]);
                // Move to the last non-overlapping interval
                int curIdx = choice[i][j];
                int l = intervals[curIdx][0];
                int lastNonOverlap = -1;
                for (int k = i - 1; k >= 1; --k) {
                    int prevIdx = idxs[k - 1];
                    if (intervals[prevIdx][1] < l) {
                        lastNonOverlap = k - 1;
                        break;
                    }
                }
                i = lastNonOverlap + 1;
                --j;
            }
        }
        reverse(result.begin(), result.end());
        return result;   
    }
};
