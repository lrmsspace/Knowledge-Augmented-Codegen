// Source: https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer mountainHeight denoting the height of a mountain.
//
// You are also given an integer array workerTimes representing the work time of workers in seconds.
//
// The workers work simultaneously to reduce the height of the mountain. For worker i:
//
//
// 	To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For example:
//
// 	
// 		To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
// 		To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.
// 	
// 	
//
//
// Return an integer representing the minimum number of seconds required for the workers to make the height of the mountain 0.
//
// Example:
// Input: mountainHeight = 4, workerTimes = [2,1,1]
//
// Output: 3
//
// Explanation:
//
// One way the height of the mountain can be reduced to 0 is:
//
//
// 	Worker 0 reduces the height by 1, taking workerTimes[0] = 2 seconds.
// 	Worker 1 reduces the height by 2, taking workerTimes[1] + workerTimes[1] * 2 = 3 seconds.
// 	Worker 2 reduces the height by 1, taking workerTimes[2] = 1 second.
//
//
// Since they work simultaneously, the minimum time needed is max(2, 3, 1) = 3 seconds.
//
// Constraints:
// 1 <= mountainHeight <= 105
// 	1 <= workerTimes.length <= 104
// 	1 <= workerTimes[i] <= 106
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} mountainHeight
 * @param {number[]} workerTimes
 * @return {number}
 */
var minNumberOfSeconds = function(mountainHeight, workerTimes) {
    let low = 0;
    let high = 1e15; // A large number to ensure we cover the maximum possible time

    while (low < high) {
        const mid = low + Math.floor((high - low) / 2);
        if (canReduceToZero(workerTimes, mountainHeight, mid)) {
            high = mid; // Try to find a smaller time
        } else {
            low = mid + 1; // Need more time
        }
    }

    return low;
};
