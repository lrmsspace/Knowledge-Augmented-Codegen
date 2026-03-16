// Source: https://leetcode.com/problems/implement-rand10-using-rand7/   |   Difficulty: Medium
//
// Problem Description:
// Given the API rand7() that generates a uniform random integer in the range [1, 7], write a function rand10() that generates a uniform random integer in the range [1, 10]. You can only call the API rand7(), and you shouldn't call any other API. Please do not use a language's built-in random API.
//
// Each test case will have one internal argument n, the number of times that your implemented function rand10() will be called while testing. Note that this is not an argument passed to rand10().
//
// Example:
// Input: n = 1
// Output: [2]
//
// Constraints:
// 1 <= n <= 105
//
//
//  
// Follow up:
//
//
// 	What is the expected value for the number of calls to rand7() function?
// 	Could you minimize the number of calls to rand7()?
//
// Helpful references (internal KB):
// - Rejection sampling (number, rejection-sampling)
//   • When to use: Used to generate random samples from a target probability distribution when direct sampling is difficult, by sampling from a simpler proposal distribution and accepting/rejecting based on a criterion.
//   • Idea: Rejection sampling generates samples from a complex target distribution by drawing from a simpler proposal distribution and accepting or rejecting samples based on a comparison with the target PDF. Its efficiency depends on the overlap between the proposal and target distributions, often leading to O(N) average time complexity per accepted sample, where N is related to the ratio of maximum PDFs.
//   • Invariants: The proposal distribution's PDF, scaled by M, always upper bounds the target distribution's PDF.; Each accepted sample is drawn from the target distribution.
//   • Tips: Choose a proposal distribution that 'envelopes' the target distribution (g(x) * M >= f(x)).; Ensure the proposal distribution is easy to sample from.
//   • Pitfalls: Low acceptance rate if proposal and target distributions differ significantly.; Inefficient if the proposal distribution's maximum is much higher than the target's.
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * The rand7() API is already defined in the parent class SolBase.
 * public int rand7();
 * @return a random integer in the range 1 to 7
 */
class Solution extends SolBase {
    public int rand10() {
        while (true) {
            int row = rand7();
            int col = rand7();
            int idx = (row - 1) * 7 + col; // [1, 49]
            if (idx <= 40) {
                return 1 + (idx - 1) % 10;
            }
            // Rejection sampling for idx in [41, 49]
            int rem = idx - 40; // [1, 9]
            row = rem;
            col = rand7();
            idx = (row - 1) * 7 + col; // [1, 63]
            if (idx <= 60) {
                return 1 + (idx - 1) % 10;
            }
            // Rejection sampling for idx in [61, 63]
            rem = idx - 60; // [1, 3]
            row = rem;
            col = rand7();
            idx = (row - 1) * 7 + col; // [1, 21]
            if (idx <= 20) {
                return 1 + (idx - 1) % 10;
            }
            // Otherwise, repeat the process
        }
    }
}
