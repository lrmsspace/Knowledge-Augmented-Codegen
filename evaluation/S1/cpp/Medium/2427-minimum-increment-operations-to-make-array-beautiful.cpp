// Source: https://leetcode.com/problems/minimum-increment-operations-to-make-array-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums having length n, and an integer k.
//
// You can perform the following increment operation any number of times (including zero):
//
//
// 	Choose an index i in the range [0, n - 1], and increase nums[i] by 1.
//
//
// An array is considered beautiful if, for any subarray with a size of 3 or more, its maximum element is greater than or equal to k.
//
// Return an integer denoting the minimum number of increment operations needed to make nums beautiful.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,3,0,0,2], k = 4
// Output: 3
// Explanation: We can perform the following increment operations to make nums beautiful:
// Choose index i = 1 and increase nums[1] by 1 -> [2,4,0,0,2].
// Choose index i = 4 and increase nums[4] by 1 -> [2,4,0,0,3].
// Choose index i = 4 and increase nums[4] by 1 -> [2,4,0,0,4].
// The subarrays with a size of 3 or more are: [2,4,0], [4,0,0], [0,0,4], [2,4,0,0], [4,0,0,4], [2,4,0,0,4].
// In all the subarrays, the maximum element is equal to k = 4, so nums is now beautiful.
// It can be shown that nums cannot be made beautiful with fewer than 3 increment operations.
// Hence, the answer is 3.
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= k <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minIncrementOperations(vector<int>& nums, int k) {
        long long operations = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (i >= 2) {
                int required_max = k;
                if (nums[i - 1] < required_max) {
                    int increment = required_max - nums[i - 1];
                    nums[i - 1] += increment;
                    operations += increment;
                }
                if (nums[i - 2] < required_max) {
                    int increment = required_max - nums[i - 2];
                    nums[i - 2] += increment;
                    operations += increment;
                }
            }
        }
        return operations;          
    }
};
