// Source: https://leetcode.com/problems/minimize-length-of-array-using-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing positive integers.
//
// Your task is to minimize the length of nums by performing the following operations any number of times (including zero):
//
//
// 	Select two distinct indices i and j from nums, such that nums[i] > 0 and nums[j] > 0.
// 	Insert the result of nums[i] % nums[j] at the end of nums.
// 	Delete the elements at indices i and j from nums.
//
//
// Return an integer denoting the minimum length of nums after performing the operation any number of times.
//
// Example:
// Input: nums = [1,4,3,1]
// Output: 1
// Explanation: One way to minimize the length of the array is as follows:
// Operation 1: Select indices 2 and 1, insert nums[2] % nums[1] at the end and it becomes [1,4,3,1,3], then delete elements at indices 2 and 1.
// nums becomes [1,1,3].
// Operation 2: Select indices 1 and 2, insert nums[1] % nums[2] at the end and it becomes [1,1,3,1], then delete elements at indices 1 and 2.
// nums becomes [1,1].
// Operation 3: Select indices 1 and 0, insert nums[1] % nums[0] at the end and it becomes [1,1,0], then delete elements at indices 1 and 0.
// nums becomes [0].
// The length of nums cannot be reduced further. Hence, the answer is 1.
// It can be shown that 1 is the minimum achievable length.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Operations on polynomials and series (array, gcd)
//   • When to use: When performing algebraic operations on polynomials or power series, such as finding their greatest common divisor, differentiation, integration, or computing series expansions like inverse, logarithm, and exponential, especially in modular arithmetic.
//   • Idea: This card details various algebraic operations on polynomials and power series, including finding their greatest common divisor (GCD) and computing derivatives, integrals, inverses, logarithms, exponentials, and powers. These operations manipulate polynomial coefficients, often within a modular arithmetic context, with many achieving O(N log N) or O(N log NK) complexity.
//   • Invariants: The degree of the resulting polynomial/series is correctly maintained after each operation.; Coefficients are always reduced modulo m if modular arithmetic is applied.
//   • Tips: Represent polynomials as arrays of coefficients, typically from lowest to highest degree.; Modular arithmetic is crucial for many polynomial operations, including GCD, to prevent overflow and ensure results stay within a finite field.
//   • Pitfalls: Forgetting to handle modular inverses for division operations (e.g., integration, polynomial division in GCD, inverse, log).; Incorrectly handling the constant term or leading coefficients, especially for inverse, logarithm, or polynomial division.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two non-negative integers, or as a subroutine for calculating the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two integers by repeatedly applying the division algorithm. It has a logarithmic time complexity, typically O(log(min(a,b))).
//   • Invariants: The GCD of the current pair (a, b) is always equal to the GCD of the original input numbers.; If a and b are non-negative, then the current values of a and b remain non-negative.
//   • Tips: The GCD of any number and zero is the number itself (e.g., gcd(a, 0) = a).; To calculate LCM, use the formula lcm(a, b) = (a / gcd(a, b)) * b to prevent potential overflow.
//   • Pitfalls: Ensure inputs are non-negative; if negative, take absolute values first.; Be careful with `gcd(0, 0)` definition, which is often undefined or 0.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd, recursion)
//   • When to use: Use when needing to find the greatest common divisor of two or more non-negative integers. It efficiently determines the largest positive integer that divides both numbers without a remainder.
//   • Idea: The Euclidean algorithm efficiently computes the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the property that gcd(a, b) = gcd(b, a mod b). Its time complexity is logarithmic with respect to the smaller of the two numbers, specifically O(log(min(a, b))).
//   • Invariants: The greatest common divisor of the two numbers remains constant throughout the algorithm.; Both numbers involved in the computation are always non-negative.
//   • Tips: Prefer the modulo-based version for significantly better performance than repeated subtraction.; Handle the base case where one number is zero; the GCD is the other non-zero number.
//   • Pitfalls: Incorrectly defining gcd(0, 0); it's often conveniently set to 0 to maintain associativity.; Using repeated subtraction for large numbers, which is much slower than the modulo operation.
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
var minimumArrayLength = function(nums) {
    const gcd = (a, b) => b === 0 ? a : gcd(b, a % b);
    
    let currentGCD = nums[0];
    for (let i = 1; i < nums.length; i++) {
        currentGCD = gcd(currentGCD, nums[i]);
        if (currentGCD === 1) {
            return 1;
        }
    }
    
    return 2;
};
