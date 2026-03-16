// Source: https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums, an integer array queries, and an integer x.
//
// For each queries[i], you need to find the index of the queries[i]th occurrence of x in the nums array. If there are fewer than queries[i] occurrences of x, the answer should be -1 for that query.
//
// Return an integer array answer containing the answers to all queries.
//
// Example:
// Input: nums = [1,3,1,7], queries = [1,3,2,4], x = 1
//
// Output: [0,-1,2,-1]
//
// Explanation:
//
//
// 	For the 1st query, the first occurrence of 1 is at index 0.
// 	For the 2nd query, there are only two occurrences of 1 in nums, so the answer is -1.
// 	For the 3rd query, the second occurrence of 1 is at index 2.
// 	For the 4th query, there are only two occurrences of 1 in nums, so the answer is -1.
//
// Constraints:
// 1 <= nums.length, queries.length <= 105
// 	1 <= queries[i] <= 105
// 	1 <= nums[i], x <= 104
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Range Minimum Query (array, tree, lca)
//   • When to use: Use when needing to find the minimum element within various specified ranges of a static array efficiently, especially when many queries are expected after initial preprocessing.
//   • Idea: Range Minimum Query (RMQ) finds the minimum value in a given contiguous subsegment of an array. It typically involves preprocessing the array to achieve O(1) or O(log N) query time, with preprocessing in O(N log N) or O(N).
//   • Invariants: For a Sparse Table `st[i][j]`, `st[i][j]` stores the minimum in the range `[i, i + 2^j - 1]`.; During a query `[L, R]`, the chosen blocks `[L, L + 2^k - 1]` and `[R - 2^k + 1, R]` completely cover the target range.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; Segment Trees provide O(log N) query and update times, suitable for dynamic arrays.
//   • Pitfalls: Sparse Tables do not support updates efficiently; they are primarily for static data.; Off-by-one errors are common when calculating range indices or log values for segment lengths.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] occurrencesOfElement(int[] nums, int[] queries, int x) {
        // Preprocess nums to store the indices of occurrences of x
        List<Integer> occurrences = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == x) {
                occurrences.add(i);
            }
        }

        // Prepare the result array
        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int k = queries[i];
            // Check if the k-th occurrence exists
            if (k <= occurrences.size()) {
                result[i] = occurrences.get(k - 1); // k is 1-based index
            } else {
                result[i] = -1; // Not enough occurrences
            }
        }

        return result;          
    }
}
