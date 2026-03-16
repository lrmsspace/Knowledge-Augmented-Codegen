// Source: https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, modify the array in the following way:
//
//
// 	choose an index i and replace nums[i] with -nums[i].
//
//
// You should apply this process exactly k times. You may choose the same index i multiple times.
//
// Return the largest possible sum of the array after modifying it in this way.
//
// Example:
// Input: nums = [4,2,3], k = 1
// Output: 5
// Explanation: Choose index 1 and nums becomes [4,-2,3].
//
// Constraints:
// 1 <= nums.length <= 104
// 	-100 <= nums[i] <= 100
// 	1 <= k <= 104
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        // Min-heap to get the smallest element efficiently
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
        }

        // Perform k negations
        for (int i = 0; i < k; ++i) {
            int smallest = minHeap.top();
            minHeap.pop();
            minHeap.push(-smallest);
        }

        // Calculate the final sum
        int totalSum = 0;
        while (!minHeap.empty()) {
            totalSum += minHeap.top();
            minHeap.pop();
        }

        return totalSum;            
    }
};
