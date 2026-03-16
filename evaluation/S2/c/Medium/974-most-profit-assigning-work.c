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
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    // Create an array of pairs (difficulty, profit) and sort it by difficulty
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

    // Sort workers by their ability
    for (int i = 0; i < workerSize - 1; i++) {
        for (int j = 0; j < workerSize - i - 1; j++) {
            if (worker[j] > worker[j + 1]) {
                int temp = worker[j];
                worker[j] = worker[j + 1];
                worker[j + 1] = temp;
            }
        }
    }

    int maxProfit = 0;
    int jobIndex = 0;

    // Iterate through each worker and assign the best job they can do
    for (int i = 0; i < workerSize; i++) {
        while (jobIndex < difficultySize && jobs[jobIndex][0] <= worker[i]) {
            if (jobs[jobIndex][1] > maxProfit) {
                maxProfit = jobs[jobIndex][1]; // Update max profit if this job is better
            }
            jobIndex++;
        }
        maxProfit += maxProfit; // Add the best profit for this worker
    }

    return maxProfit;       
}
