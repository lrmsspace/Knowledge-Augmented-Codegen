// Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// You can do the following operation on the array any number of times (possibly zero):
//
//
// 	Choose any 3 consecutive elements from the array and flip all of them.
//
//
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
//
// Return the minimum number of operations required to make all elements in nums equal to 1. If it is impossible, return -1.
//
// Example:
// Input: nums = [0,1,1,1,0,0]
//
// Output: 3
//
// Explanation:
// We can do the following operations:
//
//
// 	Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
// 	Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
// 	Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
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
var minOperations = function(nums) {
    let operations = 0;

    for (let i = 0; i < nums.length - 2; i++) {
        if (nums[i] === 0) {
            // Flip the current and the next two elements
            nums[i] = 1 - nums[i];
            nums[i + 1] = 1 - nums[i + 1];
            nums[i + 2] = 1 - nums[i + 2];
            operations++;
        }
    }

    // Check if the last two elements are both 1
    if (nums[nums.length - 2] === 0 || nums[nums.length - 1] === 0) {
        return -1; // Impossible to make all elements equal to 1
    }

    return operations;
};
