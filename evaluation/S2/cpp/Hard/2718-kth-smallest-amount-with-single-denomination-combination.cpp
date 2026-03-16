// Source: https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array coins representing coins of different denominations and an integer k.
//
// You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.
//
// Return the kth smallest amount that can be made using these coins.
//
// Example:
// Input: coins = [3,6,9], k = 3
//
// Output:  9
//
// Explanation: The given coins can make the following amounts:
// Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
// Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
// Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
// All of the coins combined produce: 3, 6, 9, 12, 15, etc.
//
// Constraints:
// 1 <= coins.length <= 15
// 	1 <= coins[i] <= 25
// 	1 <= k <= 2 * 109
// 	coins contains pairwise distinct integers.
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
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        // Step 1: Sort the coins to ensure we process them in ascending order.
        sort(coins.begin(), coins.end());

        // Step 2: Use a min-heap (priority queue) to keep track of the next smallest amounts.
        priority_queue<long long, vector<long long>, greater<long long>> minHeap;

        // Step 3: Initialize the heap with the first coin's multiples.
        for (int coin : coins) {
            minHeap.push(coin);
        }

        // Step 4: Extract the smallest amount from the heap k times.
        long long currentAmount = 0;
        for (int i = 0; i < k; ++i) {
            currentAmount = minHeap.top();
            minHeap.pop();

            // For each extracted amount, add the next multiple of the same coin to the heap.
            for (int coin : coins) {
                if (currentAmount % coin == 0) {
                    minHeap.push(currentAmount + coin);
                }
            }
        }

        return currentAmount;           
    }
};
