// Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// A special triplet is defined as a triplet of indices (i, j, k) such that:
//
//
// 	0 <= i < j < k < n, where n = nums.length
// 	nums[i] == nums[j] * 2
// 	nums[k] == nums[j] * 2
//
//
// Return the total number of special triplets in the array.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [6,3,6]
//
// Output: 1
//
// Explanation:
//
// The only special triplet is (i, j, k) = (0, 1, 2), where:
//
//
// 	nums[0] = 6, nums[1] = 3, nums[2] = 6
// 	nums[0] = nums[1] * 2 = 3 * 2 = 6
// 	nums[2] = nums[1] * 2 = 3 * 2 = 6
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int specialTriplets(int[] nums) {
        long count = 0;
        int mod = (int) 1e9 + 7;
        Map<Integer, Integer> freq = new HashMap<>();

        for (int num : nums) {
            int half = num / 2;
            if (num % 2 == 0 && freq.containsKey(half)) {
                count = (count + (long) freq.get(half) * freq.getOrDefault(half * 2, 0)) % mod) % mod;
            }
            freq.put(num, freq.getOrDefault(num, 0) + 1);
        }

        return (int) count;         
    }
}
