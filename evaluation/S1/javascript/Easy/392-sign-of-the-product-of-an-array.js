// Source: https://leetcode.com/problems/sign-of-the-product-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Implement a function signFunc(x) that returns:
//
//
// 	1 if x is positive.
// 	-1 if x is negative.
// 	0 if x is equal to 0.
//
//
// You are given an integer array nums. Let product be the product of all values in the array nums.
//
// Return signFunc(product).
//
// Example:
// Input: nums = [-1,-2,-3,-4,3,2,1]
// Output: 1
// Explanation: The product of all values in the array is 144, and signFunc(144) = 1
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-100 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
//   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
//   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
//   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
// - Operations on polynomials and series (array, recursion)
//   • When to use: Use when counting combinations or permutations with specific sum constraints, or when analyzing discrete probability distributions through polynomial multiplication.
//   • Idea: This technique represents combinatorial problems as coefficients of polynomials or formal power series. Solutions involve operations like polynomial multiplication and exponentiation, often with a time complexity dependent on the degree of the polynomials.
//   • Invariants: The degree of the product polynomial is the sum of the degrees of the input polynomials.; The coefficient of x^k in the product is the sum of A[i]*B[j] for all i+j=k.
//   • Tips: Represent individual choices as polynomial terms.; Multiply polynomials to combine independent events.
//   • Pitfalls: Incorrectly forming the initial generating function.; Naive polynomial multiplication can be computationally expensive.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var arraySign = function(nums) {
    let sign = 1;
    for (const num of nums) {
        if (num === 0) {
            return 0;
        } else if (num < 0) {
            sign = -sign;
        }
    }
    return sign;
};
