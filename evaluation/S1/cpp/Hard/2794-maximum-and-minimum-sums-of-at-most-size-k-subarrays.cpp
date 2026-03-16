// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subarrays with at most k elements.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 20
//
// Explanation:
//
// The subarrays of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subarray
// 			Minimum
// 			Maximum
// 			Sum
// 		
// 		
// 			[1]
// 			1
// 			1
// 			2
// 		
// 		
// 			[2]
// 			2
// 			2
// 			4
// 		
// 		
// 			[3]
// 			3
// 			3
// 			6
// 		
// 		
// 			[1, 2]
// 			1
// 			2
// 			3
// 		
// 		
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			20
// 		
// 	
//
//
// The output would be 20.
//
// Constraints:
// 1 <= nums.length <= 80000
// 	1 <= k <= nums.length
// 	-106 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        long long totalMaxSum = 0;
        long long totalMinSum = 0;

        // Calculate maximum sums
        deque<int> maxDeque;
        for (int i = 0; i <= n; ++i) {
            while (!maxDeque.empty() && maxDeque.front() < i - k) {
                maxDeque.pop_front();
            }
            while (!maxDeque.empty() && prefixSum[maxDeque.back()] <= prefixSum[i]) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(i);
            if (i > 0) {
                totalMaxSum += prefixSum[i] - prefixSum[maxDeque.front()];
            }
        }

        // Calculate minimum sums
        deque<int> minDeque;
        for (int i = 0; i <= n; ++i) {
            while (!minDeque.empty() && minDeque.front() < i - k) {
                minDeque.pop_front();
            }
            while (!minDeque.empty() && prefixSum[minDeque.back()] >= prefixSum[i]) {
                minDeque.pop_back();
            }
            minDeque.push_back(i);
            if (i > 0) {
                totalMinSum += prefixSum[i] - prefixSum[minDeque.front()];
            }
        }

        return totalMaxSum + totalMinSum;           
    }
};
