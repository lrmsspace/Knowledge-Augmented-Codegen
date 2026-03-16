// Source: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/   |   Difficulty: Medium
//
// Problem Description:
// Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
//
//
// 	[4,5,6,7,0,1,2] if it was rotated 4 times.
// 	[0,1,2,4,5,6,7] if it was rotated 7 times.
//
//
// Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
//
// Given the sorted rotated array nums of unique elements, return the minimum element of this array.
//
// You must write an algorithm that runs in O(log n) time.
//
// Example:
// Input: nums = [3,4,5,1,2]
// Output: 1
// Explanation: The original array was [1,2,3,4,5] rotated 3 times.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 5000
// 	-5000 <= nums[i] <= 5000
// 	All the integers of nums are unique.
// 	nums is sorted and rotated between 1 and n times.
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, quickselect, randomized)
//   • When to use: When you need to efficiently find the Kth smallest or largest element in an unsorted array. It is ideal when a full sort is unnecessary and average linear time performance is acceptable.
//   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list by repeatedly partitioning the array around a pivot. It achieves an average time complexity of O(N) and a worst-case complexity of O(N^2).
//   • Invariants: All elements in the left partition are less than or equal to the pivot element.; All elements in the right partition are greater than or equal to the pivot element.
//   • Tips: Shuffle the input array or choose a random pivot to achieve average O(N) performance.; The algorithm modifies the input array in place, so a copy might be needed if the original must be preserved.
//   • Pitfalls: A consistently bad pivot choice (e.g., always smallest/largest) leads to O(N^2) worst-case time.; Not suitable if the relative order of other elements needs to be preserved (it's not a stable algorithm).
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findMin(int[] nums) {
        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            // If mid element is greater than the rightmost element,
            // the minimum must be in the right half
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                // Otherwise, the minimum is in the left half (including mid)
                right = mid;
            }
        }

        // At the end of the loop, left == right pointing to the minimum element
        return nums[left];          
    }
}
