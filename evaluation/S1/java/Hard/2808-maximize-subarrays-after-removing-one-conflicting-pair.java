// Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
//
// Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
//
// Return the maximum number of subarrays possible after removing exactly one conflicting pair.
//
// Example:
// Input: n = 4, conflictingPairs = [[2,3],[1,4]]
//
// Output: 9
//
// Explanation:
//
//
// 	Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
// 	There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
// 	The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= conflictingPairs.length <= 2 * n
// 	conflictingPairs[i].length == 2
// 	1 <= conflictingPairs[i][j] <= n
// 	conflictingPairs[i][0] != conflictingPairs[i][1]
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long sumArray(long[] arr) {
        long sum = 0;
        for (long num : arr) {
            sum += num;
        }
        return sum;
    }
    public long maxSubarrays(int n, int[][] conflictingPairs) {
        long totalSubarrays = (long) n * (n + 1) / 2;
        int m = conflictingPairs.length;

        long[] invalidSubarrays = new long[m];
        for (int i = 0; i < m; i++) {
            int a = conflictingPairs[i][0];
            int b = conflictingPairs[i][1];
            int left = Math.min(a, b);
            int right = Math.max(a, b);
            long leftOptions = left;
            long rightOptions = n - right + 1;
            invalidSubarrays[i] = leftOptions * rightOptions;
        }

        long maxValidSubarrays = 0;
        for (int i = 0; i < m; i++) {
            long validSubarrays = totalSubarrays - (sumArray(invalidSubarrays) - invalidSubarrays[i]);
            maxValidSubarrays = Math.max(maxValidSubarrays, validSubarrays);
        }

        return maxValidSubarrays;           
    }
}
