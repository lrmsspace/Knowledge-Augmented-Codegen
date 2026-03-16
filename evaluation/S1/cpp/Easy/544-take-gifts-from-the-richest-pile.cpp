// Source: https://leetcode.com/problems/take-gifts-from-the-richest-pile/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:
//
//
// 	Choose the pile with the maximum number of gifts.
// 	If there is more than one pile with the maximum number of gifts, choose any.
// 	Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
//
//
// Return the number of gifts remaining after k seconds.
//
// Example:
// Input: gifts = [25,64,9,4,100], k = 4
// Output: 29
// Explanation: 
// The gifts are taken in the following way:
// - In the first second, the last pile is chosen and 10 gifts are left behind.
// - Then the second pile is chosen and 8 gifts are left behind.
// - After that the first pile is chosen and 5 gifts are left behind.
// - Finally, the last pile is chosen again and 3 gifts are left behind.
// The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.
//
// Constraints:
// 1 <= gifts.length <= 103
// 	1 <= gifts[i] <= 109
// 	1 <= k <= 103
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Reservoir Sampling (array, randomized, simulation)
//   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
//   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
//   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
//   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
//   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> maxHeap;
        for (int gift : gifts) {
            maxHeap.push(gift);
        }
        
        for (int i = 0; i < k; ++i) {
            int topGift = maxHeap.top();
            maxHeap.pop();
            int reducedGift = static_cast<int>(sqrt(topGift));
            maxHeap.push(reducedGift);
        }
        
        long long totalGifts = 0;
        while (!maxHeap.empty()) {
            totalGifts += maxHeap.top();
            maxHeap.pop();
        }
        
        return totalGifts;          
    }
};
