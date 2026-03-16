// Source: https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/   |   Difficulty: Hard
//
// Problem Description:
// Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i.
//
// All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).
//
// Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] (a) (Please read the explanation of the first example carefully).
//
// Return the probability that the two boxes have the same number of distinct balls. Answers within 10-5 of the actual value will be accepted as correct.
//
// Example:
// Input: balls = [1,1]
// Output: 1.00000
// Explanation: Only 2 ways to divide the balls equally:
// - A ball of color 1 to box 1 and a ball of color 2 to box 2
// - A ball of color 2 to box 1 and a ball of color 1 to box 2
// In both ways, the number of distinct colors in each box is equal. The probability is 2/2 = 1
//
// Constraints:
// 1 <= balls.length <= 8
// 	1 <= balls[i] <= 6
// 	sum(balls) is even.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Binomial Coefficients (number, enumeration)
//   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
//   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
//   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
//   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
//   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} balls
 * @return {number}
 */
var getProbability = function(balls) {
    
    const totalBalls = balls.reduce((sum, count) => sum + count, 0);
    const n = totalBalls / 2;
    const k = balls.length;
    const factorial = [1];
    for (let i = 1; i <= totalBalls; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    const countWays = (box1, box2, colorIndex) => {
        if (colorIndex === k) {
            if (box1.length === n && box2.length === n) {
                const distinct1 = new Set(box1).size;
                const distinct2 = new Set(box2).size;
                return distinct1 === distinct2 ? 1 : 0;
            }
            return 0;
        }
        let ways = 0;
        for (let i = 0; i <= balls[colorIndex]; i++) {
            box1.push(...Array(i).fill(colorIndex));
            box2.push(...Array(balls[colorIndex] - i).fill(colorIndex));
            ways += countWays(box1, box2, colorIndex + 1);
            box1.splice(-i);
            box2.splice(-(balls[colorIndex] - i));
        }
        return ways;
    }
    const totalWays = countWays([], [], 0); 
    const totalPermutations = factorial[n] * factorial[n];
    return totalWays / totalPermutations;
                
};
