// Source: https://leetcode.com/problems/maximize-the-topmost-element-after-k-moves/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the contents of a pile, where nums[0] is the topmost element of the pile.
//
// In one move, you can perform either of the following:
//
//
// 	If the pile is not empty, remove the topmost element of the pile.
// 	If there are one or more removed elements, add any one of them back onto the pile. This element becomes the new topmost element.
//
//
// You are also given an integer k, which denotes the total number of moves to be made.
//
// Return the maximum value of the topmost element of the pile possible after exactly k moves. In case it is not possible to obtain a non-empty pile after k moves, return -1.
//
// Example:
// Input: nums = [5,2,2,4,0,6], k = 4
// Output: 5
// Explanation:
// One of the ways we can end with 5 at the top of the pile after 4 moves is as follows:
// - Step 1: Remove the topmost element = 5. The pile becomes [2,2,4,0,6].
// - Step 2: Remove the topmost element = 2. The pile becomes [2,4,0,6].
// - Step 3: Remove the topmost element = 2. The pile becomes [4,0,6].
// - Step 4: Add 5 back onto the pile. The pile becomes [5,4,0,6].
// Note that this is not the only way to end with 5 at the top of the pile. It can be shown that 5 is the largest answer possible after 4 moves.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i], k <= 109
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
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximumTop(int[] nums, int k) {
        int n = nums.length;
        if (k == 0) {
            return nums[0];
        }
        if (n == 1) {
            return k % 2 == 1 ? -1 : nums[0];
        }
        int max = -1;
        for (int i = 0; i < Math.min(n, k - 1); i++) {
            max = Math.max(max, nums[i]);
        }
        if (k < n) {
            max = Math.max(max, nums[k]);
        }
        return max;         
    }
}
