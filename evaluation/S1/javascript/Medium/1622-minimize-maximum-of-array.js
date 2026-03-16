// Source: https://leetcode.com/problems/minimize-maximum-of-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums comprising of n non-negative integers.
//
// In one operation, you must:
//
//
// 	Choose an integer i such that 1 <= i < n and nums[i] > 0.
// 	Decrease nums[i] by 1.
// 	Increase nums[i - 1] by 1.
//
//
// Return the minimum possible value of the maximum integer of nums after performing any number of operations.
//
// Example:
// Input: nums = [3,7,1,6]
// Output: 5
// Explanation:
// One set of optimal operations is as follows:
// 1. Choose i = 1, and nums becomes [4,6,1,6].
// 2. Choose i = 3, and nums becomes [4,6,2,5].
// 3. Choose i = 1, and nums becomes [5,5,2,5].
// The maximum integer of nums is 5. It can be shown that the maximum number cannot be less than 5.
// Therefore, we return 5.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, greedy, dijkstra, bellman-ford)
//   • When to use: This algorithm finds a minimum-cost flow of a given amount from a source to a sink in a flow network. It is suitable when both flow capacity and edge costs are present.
//   • Idea: The successive shortest path algorithm iteratively finds augmenting paths with minimum cost in a residual graph, using shortest path algorithms like Bellman-Ford or Dijkstra with potentials, until the desired flow is achieved. Its complexity depends on the shortest path algorithm used and the number of augmentations.
//   • Invariants: The total flow pushed from source to sink never exceeds the sum of capacities of edges leaving the source.; For any edge (u, v) with flow f_uv, 0 <= f_uv <= capacity_uv.
//   • Tips: Use potentials with Dijkstra for non-negative edge costs in the residual graph.; Bellman-Ford is necessary if initial edge costs can be negative or if potentials are not used.
//   • Pitfalls: Incorrectly updating potentials can lead to wrong shortest paths.; Forgetting to add reverse edges with negative costs in the residual graph.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimizeArrayValue = function(nums) {
    let left = 0;
    let right = Math.max(...nums);
    
    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        let excess = 0;
        let isValid = true;
        
        for (let i = nums.length - 1; i >= 0; i--) {
            if (nums[i] + excess > mid) {
                excess = nums[i] + excess - mid;
            } else {
                excess = 0;
            }
        }
        
        if (excess > 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
};
