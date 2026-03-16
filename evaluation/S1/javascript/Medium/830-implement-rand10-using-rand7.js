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
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * The rand7() API is already defined for you.
 * var rand7 = function() {}
 * @return {number} a random integer in the range 1 to 7
 */
var rand10 = function() {
    while (true) {
        // Generate a random number in the range [1, 49] using two calls to rand7()
        const num = (rand7() - 1) * 7 + rand7(); // num is in the range [1, 49]
        
        // Only consider numbers in the range [1, 40], which can be evenly divided into groups of 10
        if (num <= 40) {
            return (num - 1) % 10 + 1; // Map the numbers to the range [1, 10]
        }
        // If num is greater than 40, we reject it and try again
    }
};
