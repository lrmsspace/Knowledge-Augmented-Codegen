// Source: https://leetcode.com/problems/find-the-k-sum-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. You can choose any subsequence of the array and sum all of its elements together.
//
// We define the K-Sum of the array as the kth largest subsequence sum that can be obtained (not necessarily distinct).
//
// Return the K-Sum of the array.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Note that the empty subsequence is considered to have a sum of 0.
//
// Example:
// Input: nums = [2,4,-2], k = 5
// Output: 2
// Explanation: All the possible subsequence sums that we can obtain are the following sorted in decreasing order:
// 6, 4, 4, 2, 2, 0, 0, -2.
// The 5-Sum of the array is 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= k <= min(2000, 2n)
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
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var kSum = function(nums, k) {
    const minHeap = new MinPriorityQueue();
    const n = nums.length;
    const sortedNums = nums.sort((a, b) => b - a);
    const initialSum = sortedNums.reduce((a, b) => a + b, 0);
    minHeap.enqueue({ sum: initialSum, index: 0 });
    for (let i = 1; i < k; i++) {
        const { sum, index } = minHeap.dequeue().element;
        if (index < n) {
            minHeap.enqueue({ sum: sum - sortedNums[index], index: index + 1 });
            if (index > 0) {
                minHeap.enqueue({ sum: sum - sortedNums[index] + sortedNums[index - 1], index: index + 1 });
            }
        }
    }
    return minHeap.dequeue().element.sum;
};
