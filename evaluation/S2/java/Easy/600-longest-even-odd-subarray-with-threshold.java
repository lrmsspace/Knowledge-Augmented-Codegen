// Source: https://leetcode.com/problems/longest-even-odd-subarray-with-threshold/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer threshold.
//
// Find the length of the longest subarray of nums starting at index l and ending at index r (0 <= l <= r < nums.length) that satisfies the following conditions:
//
//
// 	nums[l] % 2 == 0
// 	For all indices i in the range [l, r - 1], nums[i] % 2 != nums[i + 1] % 2
// 	For all indices i in the range [l, r], nums[i] <= threshold
//
//
// Return an integer denoting the length of the longest such subarray.
//
// Note: A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [3,2,5,4], threshold = 5
// Output: 3
// Explanation: In this example, we can select the subarray that starts at l = 1 and ends at r = 3 => [2,5,4]. This subarray satisfies the conditions.
// Hence, the answer is the length of the subarray, 3. We can show that 3 is the maximum possible achievable length.
//
// Constraints:
// 1 <= nums.length <= 100 
// 	1 <= nums[i] <= 100 
// 	1 <= threshold <= 100
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int longestAlternatingSubarray(int[] nums, int threshold) {
        int maxLength = 0;
        int currentLength = 0;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] <= threshold && (currentLength == 0 || (nums[i] % 2 != nums[i - 1] % 2))) {
                currentLength++;
            } else {
                maxLength = Math.max(maxLength, currentLength);
                currentLength = (nums[i] <= threshold && nums[i] % 2 == 0) ? 1 : 0;
            }
        }

        return Math.max(maxLength, currentLength);          
    }
}
