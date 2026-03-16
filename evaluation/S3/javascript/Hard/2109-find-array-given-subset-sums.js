// Source: https://leetcode.com/problems/find-array-given-subset-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).
//
// Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.
//
// An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.
//
// Note: Test cases are generated such that there will always be at least one correct answer.
//
// Example:
// Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
// Output: [1,2,-3]
// Explanation: [1,2,-3] is able to achieve the given subset sums:
// - []: sum is 0
// - [1]: sum is 1
// - [2]: sum is 2
// - [1,2]: sum is 3
// - [-3]: sum is -3
// - [1,-3]: sum is -2
// - [2,-3]: sum is -1
// - [1,2,-3]: sum is 0
// Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
//
// Constraints:
// 1 <= n <= 15
// 	sums.length == 2n
// 	-104 <= sums[i] <= 104
//
// Helpful references (internal KB):
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Operations on polynomials and series (array, divide-and-conquer, recursion)
//   • When to use: When performing arithmetic operations like multiplication, division, or inversion on polynomials or formal power series, especially for large degrees where naive O(N^2) approaches are too slow.
//   • Idea: This involves algorithms for arithmetic operations on polynomials and formal power series, often leveraging divide-and-conquer techniques like Fast Fourier Transform (FFT) for efficient O(N log N) multiplication.
//   • Invariants: The coefficient array A represents polynomial A(x) such that A[i] is the coefficient of x^i.; The degree of the resulting polynomial is correctly calculated based on the input polynomials' degrees.
//   • Tips: Represent polynomials as arrays of coefficients, typically from lowest to highest degree.; Pad coefficient arrays with zeros to the next power of two for FFT-based multiplication.
//   • Pitfalls: Incorrectly handling polynomial degrees and array sizes, leading to off-by-one errors or out-of-bounds access.; Numerical precision issues when using floating-point FFT for polynomial multiplication.
// - Operations on polynomials and series (array, recursion)
//   • When to use: When you need to compute the product of two polynomials or formal power series, often represented by their coefficient arrays. This is useful for combining algebraic expressions or solving recurrence relations.
//   • Idea: This involves computing the coefficients of the product polynomial by convolving the coefficients of the input polynomials. Algorithms like Karatsuba's use a divide-and-conquer recursive approach to achieve better than naive quadratic time complexity.
//   • Invariants: Each recursive call correctly computes the product of its two input sub-polynomials; The base case for recursion (e.g., constant polynomials) is handled correctly
//   • Tips: Represent polynomials as arrays of coefficients; Pad shorter polynomials with zeros to match degrees
//   • Pitfalls: Forgetting to handle zero coefficients or different polynomial degrees; Naive O(N^2) multiplication can be too slow for large inputs
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} sums
 * @return {number[]}
 */
var recoverArray = function(n, sums) {
    sums.sort((a, b) => a - b);
    const ans = [];
    for (let i = 0; i < n; i++) {
        const diff = sums[1] - sums[0];
        ans.push(diff);
        const count = new Map();
        for (const sum of sums) {
            count.set(sum, (count.get(sum) || 0) + 1);
        }
        const newSums = [];
        for (const sum of sums) {
            if (count.get(sum) > 0) {
                newSums.push(sum);
                count.set(sum, count.get(sum) - 1);
                count.set(sum + diff, count.get(sum + diff) - 1);
            }
        }
        sums = newSums;
    }
    return ans;
        
};
