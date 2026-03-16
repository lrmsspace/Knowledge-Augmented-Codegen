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
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
        long long ans = 0;
        int n = nums.size();
        for (int i = 2; i < n; ++i) {
            if (nums[i - 2] >= k) {
                continue;
            }
            int need = k - nums[i - 2];
            nums[i - 2] += need;
            ans += need;
        }
        return ans;         
    }
};
