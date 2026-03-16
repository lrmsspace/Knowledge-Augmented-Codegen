// Source: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/   |   Difficulty: Hard
//
// Problem Description:
// You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs j where 0 <= j < i).
//
// You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done on that day.
//
// You are given an integer array jobDifficulty and an integer d. The difficulty of the ith job is jobDifficulty[i].
//
// Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.
//
// Example:
// Input: jobDifficulty = [6,5,4,3,2,1], d = 2
// Output: 7
// Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
// Second day you can finish the last job, total difficulty = 1.
// The difficulty of the schedule = 6 + 1 = 7
//
// Constraints:
// 1 <= jobDifficulty.length <= 300
// 	0 <= jobDifficulty[i] <= 1000
// 	1 <= d <= 10
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} jobDifficulty
 * @param {number} d
 * @return {number}
 */
var minDifficulty = function(jobDifficulty, d) {
    const n = jobDifficulty.length;
    if (n < d) return -1;

    const dp = Array.from({ length: d }, () => Array(n).fill(Infinity));
    dp[0][0] = jobDifficulty[0];

    for (let i = 1; i < n; i++) {
        dp[0][i] = Math.max(dp[0][i - 1], jobDifficulty[i]);
    }

    for (let day = 1; day < d; day++) {
        for (let job = day; job < n; job++) {
            let maxDifficulty = jobDifficulty[job];
            for (let k = job - 1; k >= day - 1; k--) {
                maxDifficulty = Math.max(maxDifficulty, jobDifficulty[k]);
                dp[day][job] = Math.min(dp[day][job], dp[day - 1][k] + maxDifficulty);
            }
        }
    }

    return dp[d - 1][n - 1];
};
