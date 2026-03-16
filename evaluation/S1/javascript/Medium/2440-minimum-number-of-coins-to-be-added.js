// Source: https://leetcode.com/problems/minimum-number-of-coins-to-be-added/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array coins, representing the values of the coins available, and an integer target.
//
// An integer x is obtainable if there exists a subsequence of coins that sums to x.
//
// Return the minimum number of coins of any value that need to be added to the array so that every integer in the range [1, target] is obtainable.
//
// A subsequence of an array is a new non-empty array that is formed from the original array by deleting some (possibly none) of the elements without disturbing the relative positions of the remaining elements.
//
// Example:
// Input: coins = [1,4,10], target = 19
// Output: 2
// Explanation: We need to add coins 2 and 8. The resulting array will be [1,2,4,8,10].
// It can be shown that all integers from 1 to 19 are obtainable from the resulting array, and that 2 is the minimum number of coins that need to be added to the array.
//
// Constraints:
// 1 <= target <= 105
// 	1 <= coins.length <= 105
// 	1 <= coins[i] <= target
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} coins
 * @param {number} target
 * @return {number}
 */
var minimumAddedCoins = function(coins, target) {
    coins.sort((a, b) => a - b);
    let missing = 1;
    let count = 0;
    for (const coin of coins) {
        if (coin > missing) {
            count += Math.ceil((coin - missing) / missing);
            missing += Math.ceil((coin - missing) / missing) * missing;
        }
        missing += coin;
        if (missing > target) {
            break;
        }
    }
    if (missing <= target) {
        count += Math.ceil((target - missing + 1) / missing);
    }
    return count;
};
