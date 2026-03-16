// Source: https://leetcode.com/problems/removing-minimum-and-maximum-from-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of distinct integers nums.
//
// There is an element in nums that has the lowest value and an element that has the highest value. We call them the minimum and maximum respectively. Your goal is to remove both these elements from the array.
//
// A deletion is defined as either removing an element from the front of the array or removing an element from the back of the array.
//
// Return the minimum number of deletions it would take to remove both the minimum and maximum element from the array.
//
// Example:
// Input: nums = [2,10,7,5,4,1,8,6]
// Output: 5
// Explanation: 
// The minimum element in the array is nums[5], which is 1.
// The maximum element in the array is nums[1], which is 10.
// We can remove both the minimum and maximum by removing 2 elements from the front and 3 elements from the back.
// This results in 2 + 3 = 5 deletions, which is the minimum number possible.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	The integers in nums are distinct.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumDeletions(int* nums, int numsSize) {
    int min_index = 0, max_index = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[min_index]) {
            min_index = i;
        }
        if (nums[i] > nums[max_index]) {
            max_index = i;
        }
    }

    int left_deletions = (min_index < max_index) ? max_index + 1 : min_index + 1;
    int right_deletions = (min_index > max_index) ? numsSize - max_index : numsSize - min_index;
    int cross_deletions = (min_index < max_index) ? (min_index + 1) + (numsSize - max_index) : (max_index + 1) + (numsSize - min_index);

    int min_deletions = left_deletions < right_deletions ? left_deletions : right_deletions;
    return min_deletions < cross_deletions ? min_deletions : cross_deletions;       
}
