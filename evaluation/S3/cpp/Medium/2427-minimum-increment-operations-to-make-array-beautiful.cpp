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
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
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
        for (int i = 2; i < nums.size(); ++i) {
            int max_prev = max(nums[i - 1], nums[i - 2]);
            if (nums[i] <= max_prev) {
                int inc = max_prev + 1 - nums[i];
                ans += inc;
                nums[i] += inc;
            }
        }
        return ans;         
    }
};
