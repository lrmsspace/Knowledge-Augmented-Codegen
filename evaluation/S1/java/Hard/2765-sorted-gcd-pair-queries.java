// Source: https://leetcode.com/problems/sorted-gcd-pair-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and an integer array queries.
//
// Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
//
// For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
//
// Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
//
// The term gcd(a, b) denotes the greatest common divisor of a and b.
//
// Example:
// Input: nums = [2,3,4], queries = [0,2,2]
//
// Output: [1,2,2]
//
// Explanation:
//
// gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
//
// After sorting in ascending order, gcdPairs = [1, 1, 2].
//
// So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].
//
// Constraints:
// 2 <= n == nums.length <= 105
// 	1 <= nums[i] <= 5 * 104
// 	1 <= queries.length <= 105
// 	0 <= queries[i] < n * (n - 1) / 2
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        int maxNum = 50000;
        int[] freq = new int[maxNum + 1];
        for (int num : nums) {
            freq[num]++;
        }

        int[] countMultiples = new int[maxNum + 1];
        for (int i = 1; i <= maxNum; i++) {
            for (int j = i; j <= maxNum; j += i) {
                countMultiples[i] += freq[j];
            }
        }

        long[] gcdCount = new long[maxNum + 1];
        for (int g = maxNum; g >= 1; g--) {
            long totalPairs = ((long) countMultiples[g] * (countMultiples[g] - 1)) / 2;
            for (int multiple = 2 * g; multiple <= maxNum; multiple += g) {
                totalPairs -= gcdCount[multiple];
            }
            gcdCount[g] = totalPairs;
        }

        long[] prefixGcdCount = new long[maxNum + 1];
        for (int i = 1; i <= maxNum; i++) {
            prefixGcdCount[i] = prefixGcdCount[i - 1] + gcdCount[i];
        }

        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            long query = queries[i];
            int left = 1, right = maxNum;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (prefixGcdCount[mid] > query) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            result[i] = left;
        }

        return result;          
    }
}
