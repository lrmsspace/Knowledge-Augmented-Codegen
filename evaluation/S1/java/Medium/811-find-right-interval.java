// Source: https://leetcode.com/problems/find-right-interval/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.
//
// The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. Note that i may equal j.
//
// Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.
//
// Example:
// Input: intervals = [[1,2]]
// Output: [-1]
// Explanation: There is only one interval in the collection, so it outputs -1.
//
// Constraints:
// 1 <= intervals.length <= 2 * 104
// 	intervals[i].length == 2
// 	-106 <= starti <= endi <= 106
// 	The start point of each interval is unique.
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    
    private int binarySearch(int[][] startWithIndex, int target) {
        int left = 0, right = startWithIndex.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (startWithIndex[mid][0] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left < startWithIndex.length ? left : -1;
    }

    public int[] findRightInterval(int[][] intervals) {
        int n = intervals.length;
        int[][] startWithIndex = new int[n][2];
        for (int i = 0; i < n; i++) {
            startWithIndex[i][0] = intervals[i][0];
            startWithIndex[i][1] = i;
        }
        java.util.Arrays.sort(startWithIndex, java.util.Comparator.comparingInt(a -> a[0]));

        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            int end = intervals[i][1];
            int index = binarySearch(startWithIndex, end);
            result[i] = index == -1 ? -1 : startWithIndex[index][1];
        }
        return result;          
    }
}
