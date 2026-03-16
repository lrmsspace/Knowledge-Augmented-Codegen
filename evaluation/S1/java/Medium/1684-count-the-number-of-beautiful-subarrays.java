// Source: https://leetcode.com/problems/count-the-number-of-beautiful-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. In one operation, you can:
//
//
// 	Choose two different indices i and j such that 0 <= i, j < nums.length.
// 	Choose a non-negative integer k such that the kth bit (0-indexed) in the binary representation of nums[i] and nums[j] is 1.
// 	Subtract 2k from nums[i] and nums[j].
//
//
// A subarray is beautiful if it is possible to make all of its elements equal to 0 after applying the above operation any number of times (including zero).
//
// Return the number of beautiful subarrays in the array nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Note: Subarrays where all elements are initially 0 are considered beautiful, as no operation is needed.
//
// Example:
// Input: nums = [4,3,1,2,4]
// Output: 2
// Explanation: There are 2 beautiful subarrays in nums: [4,3,1,2,4] and [4,3,1,2,4].
// - We can make all elements in the subarray [3,1,2] equal to 0 in the following way:
//   - Choose [3, 1, 2] and k = 1. Subtract 21 from both numbers. The subarray becomes [1, 1, 0].
//   - Choose [1, 1, 0] and k = 0. Subtract 20 from both numbers. The subarray becomes [0, 0, 0].
// - We can make all elements in the subarray [4,3,1,2,4] equal to 0 in the following way:
//   - Choose [4, 3, 1, 2, 4] and k = 2. Subtract 22 from both numbers. The subarray becomes [0, 3, 1, 2, 0].
//   - Choose [0, 3, 1, 2, 0] and k = 0. Subtract 20 from both numbers. The subarray becomes [0, 2, 0, 2, 0].
//   - Choose [0, 2, 0, 2, 0] and k = 1. Subtract 21 from both numbers. The subarray becomes [0, 0, 0, 0, 0].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long beautifulSubarrays(int[] nums) {
        Map<Integer, Integer> prefixXorCount = new HashMap<>();
        prefixXorCount.put(0, 1); // Initial prefix XOR is 0

        int prefixXor = 0;
        long beautifulSubarrayCount = 0;

        for (int num : nums) {
            prefixXor ^= num;

            // If this prefix XOR has been seen before, it means there are
            // subarrays ending at the current index that have XOR 0
            beautifulSubarrayCount += prefixXorCount.getOrDefault(prefixXor, 0);

            // Update the count of this prefix XOR
            prefixXorCount.put(prefixXor, prefixXorCount.getOrDefault(prefixXor, 0) + 1);
        }

        return beautifulSubarrayCount;          
    }
}
