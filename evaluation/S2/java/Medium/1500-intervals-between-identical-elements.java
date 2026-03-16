// Source: https://leetcode.com/problems/intervals-between-identical-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of n integers arr.
//
// The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.
//
// Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].
//
// Note: |x| is the absolute value of x.
//
// Example:
// Input: arr = [2,1,3,1,2,3,3]
// Output: [4,2,7,2,4,4,5]
// Explanation:
// - Index 0: Another 2 is found at index 4. |0 - 4| = 4
// - Index 1: Another 1 is found at index 3. |1 - 3| = 2
// - Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
// - Index 3: Another 1 is found at index 1. |3 - 1| = 2
// - Index 4: Another 2 is found at index 0. |4 - 0| = 4
// - Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
// - Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
//
// Constraints:
// n == arr.length
// 	1 <= n <= 105
// 	1 <= arr[i] <= 105
//
//
//  
// Note: This question is the same as  2615: Sum of Distances.
//
// Helpful references (internal KB):
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long[] getDistances(int[] arr) {
        int n = arr.length;
        long[] result = new long[n];
        Map<Integer, List<Integer>> indicesMap = new HashMap<>();

        // Group indices by their corresponding values in arr
        for (int i = 0; i < n; i++) {
            indicesMap.computeIfAbsent(arr[i], k -> new ArrayList<>()).add(i);
        }

        // Calculate the sum of intervals for each group of identical elements
        for (List<Integer> indices : indicesMap.values()) {
            int m = indices.size();
            long prefixSum = 0;

            // Calculate prefix sums to efficiently compute intervals
            for (int i = 0; i < m; i++) {
                int index = indices.get(i);
                result[index] += (long) index * i - prefixSum; // Intervals to previous elements
                prefixSum += index; // Update prefix sum with current index
            }

            long suffixSum = 0;
            for (int i = m - 1; i >= 0; i--) {
                int index = indices.get(i);
                result[index] += suffixSum - (long) index * (m - 1 - i); // Intervals to subsequent elements
                suffixSum += index; // Update suffix sum with current index
            }
        }

        return result;          
    }
}
