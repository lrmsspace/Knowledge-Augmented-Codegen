// Source: https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array items of length n and an integer k.
//
// items[i] = [profiti, categoryi], where profiti and categoryi denote the profit and category of the ith item respectively.
//
// Let's define the elegance of a subsequence of items as total_profit + distinct_categories2, where total_profit is the sum of all profits in the subsequence, and distinct_categories is the number of distinct categories from all the categories in the selected subsequence.
//
// Your task is to find the maximum elegance from all subsequences of size k in items.
//
// Return an integer denoting the maximum elegance of a subsequence of items with size exactly k.
//
// Note: A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order.
//
// Example:
// Input: items = [[3,2],[5,1],[10,1]], k = 2
// Output: 17
// Explanation: In this example, we have to select a subsequence of size 2.
// We can select items[0] = [3,2] and items[2] = [10,1].
// The total profit in this subsequence is 3 + 10 = 13, and the subsequence contains 2 distinct categories [2,1].
// Hence, the elegance is 13 + 22 = 17, and we can show that it is the maximum achievable elegance.
//
// Constraints:
// 1 <= items.length == n <= 105
// 	items[i].length == 2
// 	items[i][0] == profiti
// 	items[i][1] == categoryi
// 	1 <= profiti <= 109
// 	1 <= categoryi <= n 
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
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
 * @param {number[][]} items
 * @param {number} k
 * @return {number}
 */
var findMaximumElegance = function(items, k) {
    items.sort((a, b) => b[0] - a[0]);
    const categoryCount = new Map();
    const duplicates = [];
    let totalProfit = 0;

    for (let i = 0; i < k; i += 1) {
        const [profit, category] = items[i];
        totalProfit += profit;

        if (categoryCount.has(category)) {
            duplicates.push(profit);
            categoryCount.set(category, categoryCount.get(category) + 1);
        } else {
            categoryCount.set(category, 1);
        }
    }

    let elegance = totalProfit + categoryCount.size ** 2;

    for (let i = k; i < items.length && duplicates.length > 0; i += 1) {
        const [profit, category] = items[i];

        if (categoryCount.has(category)) {
            categoryCount.set(category, categoryCount.get(category) + 1);
        } else if (duplicates.length > 0) {
            const removedProfit = duplicates.pop();
            totalProfit += profit - removedProfit;
            elegance = Math.max(elegance, totalProfit + (categoryCount.size + 1) ** 2);
            categoryCount.set(category, 1);
        }
    }

    return elegance;
};
