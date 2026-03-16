// Source: https://leetcode.com/problems/airplane-seat-assignment-probability/   |   Difficulty: Medium
//
// Problem Description:
// n passengers board an airplane with exactly n seats. The first passenger has lost the ticket and picks a seat randomly. But after that, the rest of the passengers will:
//
//
// 	Take their own seat if it is still available, and
// 	Pick other seats randomly when they find their seat occupied
//
//
// Return the probability that the nth person gets his own seat.
//
// Example:
// Input: n = 1
// Output: 1.00000
// Explanation: The first person can only get the first seat.
//
// Constraints:
// 1 <= n <= 105
//
// Helpful references (internal KB):
// - Binomial Coefficients (number, enumeration)
//   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
//   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
//   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
//   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
//   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
// - Rejection sampling (number, rejection-sampling, probability-statistics)
//   • When to use: Use when you need to sample from a target probability distribution whose normalizing constant is unknown or difficult to compute, by leveraging an easier-to-sample proposal distribution.
//   • Idea: Rejection sampling generates samples from a target distribution f by drawing from a proposal distribution g and accepting/rejecting based on a uniform random number and a specific ratio. This method has an average time complexity of O(M) per accepted sample, where M is the constant bounding f(x)/g(x).
//   • Invariants: The ratio f(y) / (M * g(y)) is always between 0 and 1 (inclusive).; The proposal y is a valid sample drawn from the distribution Y with density g.
//   • Tips: Choose a proposal distribution g that is easy to sample from and closely resembles f.; Ensure the constant M is chosen such that f(x) <= M*g(x) for all x.
//   • Pitfalls: Low acceptance rate if the proposal distribution g is a poor fit for f.; Finding an optimal constant M can be challenging, especially in high dimensions.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        if (n == 1) {
            return 1.0;
        }
        return 0.5;
    }
};
