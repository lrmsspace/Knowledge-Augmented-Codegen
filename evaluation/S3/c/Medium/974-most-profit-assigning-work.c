// Source: https://leetcode.com/problems/most-profit-assigning-work/   |   Difficulty: Medium
//
// Problem Description:
// You have n jobs and m workers. You are given three arrays: difficulty, profit, and worker where:
//
//
// 	difficulty[i] and profit[i] are the difficulty and the profit of the ith job, and
// 	worker[j] is the ability of jth worker (i.e., the jth worker can only complete a job with difficulty at most worker[j]).
//
//
// Every worker can be assigned at most one job, but one job can be completed multiple times.
//
//
// 	For example, if three workers attempt the same job that pays $1, then the total profit will be $3. If a worker cannot complete any job, their profit is $0.
//
//
// Return the maximum profit we can achieve after assigning the workers to the jobs.
//
// Example:
// Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
// Output: 100
// Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get a profit of [20,20,30,30] separately.
//
// Constraints:
// n == difficulty.length
// 	n == profit.length
// 	m == worker.length
// 	1 <= n, m <= 104
// 	1 <= difficulty[i], profit[i], worker[i] <= 105
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    // Step 1: Create an array of job pairs (difficulty, profit) and sort it by difficulty
    int jobs[difficultySize][2];
    for (int i = 0; i < difficultySize; i++) {
        jobs[i][0] = difficulty[i];
        jobs[i][1] = profit[i];
    }
    // Sort jobs by difficulty
    for (int i = 0; i < difficultySize - 1; i++) {
        for (int j = 0; j < difficultySize - i - 1; j++) {
            if (jobs[j][0] > jobs[j + 1][0]) {
                int temp[2];
                temp[0] = jobs[j][0];
                temp[1] = jobs[j][1];
                jobs[j][0] = jobs[j + 1][0];
                jobs[j][1] = jobs[j + 1][1];
                jobs[j + 1][0] = temp[0];
                jobs[j + 1][1] = temp[1];
            }
        }
    }

    // Step 2: Create an array to store the maximum profit for each worker
    int maxProfitForWorker[workerSize];
    for (int i = 0; i < workerSize; i++) {
        maxProfitForWorker[i] = 0;
    }

    // Step 3: For each worker, find the best job they can do and calculate total profit
    int totalProfit = 0;
    for (int i = 0; i < workerSize; i++) {
        int ability = worker[i];
        int bestProfit = 0;
        for (int j = 0; j < difficultySize; j++) {
            if (jobs[j][0] <= ability) {
                if (jobs[j][1] > bestProfit) {
                    bestProfit = jobs[j][1];
                }
            } else {
                break; // Since jobs are sorted by difficulty, no need to check further
            }
        }
        maxProfitForWorker[i] = bestProfit;
        totalProfit += bestProfit;
    }

    return totalProfit;     
}
