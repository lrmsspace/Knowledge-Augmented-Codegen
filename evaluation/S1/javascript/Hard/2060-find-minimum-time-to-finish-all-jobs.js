// Source: https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array jobs, where jobs[i] is the amount of time it takes to complete the ith job.
//
// There are k workers that you can assign jobs to. Each job should be assigned to exactly one worker. The working time of a worker is the sum of the time it takes to complete all jobs assigned to them. Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.
//
// Return the minimum possible maximum working time of any assignment.
//
// Example:
// Input: jobs = [3,2,3], k = 3
// Output: 3
// Explanation: By assigning each person one job, the maximum time is 3.
//
// Constraints:
// 1 <= k <= jobs.length <= 12
// 	1 <= jobs[i] <= 107
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} jobs
 * @param {number} k
 * @return {number}
 */
var minimumTimeRequired = function(jobs, k) {
    const n = jobs.length;
    const totalTime = jobs.reduce((a, b) => a + b, 0);
    const maxTime = Math.max(...jobs);

    let low = maxTime;
    let high = totalTime;

    const canFinish = (limit) => {
        const workloads = new Array(k).fill(0);

        const backtrack = (index) => {
            if (index === n) {
                return true;
            }

            for (let i = 0; i < k; i++) {
                if (workloads[i] + jobs[index] <= limit) {
                    workloads[i] += jobs[index];
                    if (backtrack(index + 1)) {
                        return true;
                    }
                    workloads[i] -= jobs[index];
                }
                if (workloads[i] === 0) {
                    break; // No need to try further workers if this one is still at 0
                }
            }
            return false;
        };

        return backtrack(0);
    };

    while (low < high) {
        const mid = Math.floor((low + high) / 2);
        if (canFinish(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return low;
};
