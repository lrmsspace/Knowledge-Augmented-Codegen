// Source: https://leetcode.com/problems/eat-pizzas/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array pizzas of size n, where pizzas[i] represents the weight of the ith pizza. Every day, you eat exactly 4 pizzas. Due to your incredible metabolism, when you eat pizzas of weights W, X, Y, and Z, where W <= X <= Y <= Z, you gain the weight of only 1 pizza!
//
//
// 	On odd-numbered days (1-indexed), you gain a weight of Z.
// 	On even-numbered days, you gain a weight of Y.
//
//
// Find the maximum total weight you can gain by eating all pizzas optimally.
//
// Note: It is guaranteed that n is a multiple of 4, and each pizza can be eaten only once.
//
// Example:
// Input: pizzas = [1,2,3,4,5,6,7,8]
//
// Output: 14
//
// Explanation:
//
//
// 	On day 1, you eat pizzas at indices [1, 2, 4, 7] = [2, 3, 5, 8]. You gain a weight of 8.
// 	On day 2, you eat pizzas at indices [0, 3, 5, 6] = [1, 4, 6, 7]. You gain a weight of 6.
//
//
// The total weight gained after eating all the pizzas is 8 + 6 = 14.
//
// Constraints:
// 4 <= n == pizzas.length <= 2 * 105
// 	1 <= pizzas[i] <= 105
// 	n is a multiple of 4.
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} pizzas
 * @return {number}
 */
var maxWeight = function(pizzas) {
    pizzas.sort((a, b) => a - b);
    let score = 0;
    for (let i = pizzas.length - 1; i >= 0; i -= 4) {
        score += pizzas[i];
    }
    return score;
};
