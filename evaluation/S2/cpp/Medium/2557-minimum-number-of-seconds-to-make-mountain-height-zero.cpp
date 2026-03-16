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
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Operations on polynomials and series (array, recursion)
//   • When to use: When you need to model and solve combinatorial counting problems using algebraic methods, especially when dealing with recurrence relations or products of independent choices. It's also useful for analyzing properties of sequences.
//   • Idea: This involves performing algebraic operations like addition, multiplication, and composition on polynomials or formal power series, represented by coefficients. These operations model combinatorial structures and solve recurrence relations, typically with complexities from O(N) to O(N log N).
//   • Invariants: The array `coefficients[i]` stores the coefficient of `x^i` for the current polynomial.; For any intermediate product `C(x) = A(x) * B(x)`, the coefficient `C[k]` correctly accumulates `A[i] * B[j]` for all `i+j=k`.
//   • Tips: Represent polynomials as arrays of coefficients; Understand the combinatorial meaning of operations (e.g., product for independent choices)
//   • Pitfalls: Confusing ordinary and exponential generating functions; Incorrectly applying convolution for non-independent events
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        // Sort worker times in descending order to maximize the height reduction per worker
        sort(workerTimes.rbegin(), workerTimes.rend());

        long long totalSeconds = 0;
        int remainingHeight = mountainHeight;

        for (int time : workerTimes) {
            if (remainingHeight <= 0) {
                break; // Mountain is already reduced to zero
            }

            // Calculate how much height this worker can reduce
            int maxReduction = (remainingHeight + time - 1) / time; // Ceiling division
            int actualReduction = min(maxReduction, remainingHeight);
            totalSeconds += (long long)time * actualReduction * (actualReduction + 1) / 2; // Sum of arithmetic series
            remainingHeight -= actualReduction;
        }

        return totalSeconds;            
    }
};
