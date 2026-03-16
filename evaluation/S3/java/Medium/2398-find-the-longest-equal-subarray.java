// Source: https://leetcode.com/problems/find-the-longest-equal-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// A subarray is called equal if all of its elements are equal. Note that the empty subarray is an equal subarray.
//
// Return the length of the longest possible equal subarray after deleting at most k elements from nums.
//
// A subarray is a contiguous, possibly empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,1,3], k = 3
// Output: 3
// Explanation: It's optimal to delete the elements at index 2 and index 4.
// After deleting them, nums becomes equal to [1, 3, 3, 3].
// The longest equal subarray starts at i = 1 and ends at j = 3 with length equal to 3.
// It can be proven that no longer equal subarrays can be created.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= nums.length
// 	0 <= k <= nums.length
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int longestEqualSubarray(List<Integer> nums, int k) {
        int maxLength = 0;
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        int left = 0;

        for (int right = 0; right < nums.size(); right++) {
            int currentNum = nums.get(right);
            frequencyMap.put(currentNum, frequencyMap.getOrDefault(currentNum, 0) + 1);

            while ((right - left + 1) - Collections.max(frequencyMap.values()) > k) {
                int leftNum = nums.get(left);
                frequencyMap.put(leftNum, frequencyMap.get(leftNum) - 1);
                if (frequencyMap.get(leftNum) == 0) {
                    frequencyMap.remove(leftNum);
                }
                left++;
            }

            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;           
    }
}
