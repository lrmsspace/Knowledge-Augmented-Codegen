// Source: https://leetcode.com/problems/find-the-maximum-divisibility-score/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums and divisors.
//
// The divisibility score of divisors[i] is the number of indices j such that nums[j] is divisible by divisors[i].
//
// Return the integer divisors[i] with the maximum divisibility score. If multiple integers have the maximum score, return the smallest one.
//
// Example:
// Input: nums = [2,9,15,50], divisors = [5,3,7,2]
//
// Output: 2
//
// Explanation:
//
// The divisibility score of divisors[0] is 2 since nums[2] and nums[3] are divisible by 5.
//
// The divisibility score of divisors[1] is 2 since nums[1] and nums[2] are divisible by 3.
//
// The divisibility score of divisors[2] is 0 since none of the numbers in nums is divisible by 7.
//
// The divisibility score of divisors[3] is 2 since nums[0] and nums[3] are divisible by 2.
//
// As divisors[0], divisors[1], and divisors[3] have the same divisibility score, we return the smaller one which is divisors[3].
//
// Constraints:
// 1 <= nums.length, divisors.length <= 1000
// 	1 <= nums[i], divisors[i] <= 109
//
// Helpful references (internal KB):
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[]} divisors
 * @return {number}
 */
var maxDivScore = function(nums, divisors) {
    let maxScore = -1;
    let resultDivisor = -1;

    for (let divisor of divisors) {
        let score = 0;
        for (let num of nums) {
            if (num % divisor === 0) {
                score++;
            }
        }
        if (score > maxScore || (score === maxScore && divisor < resultDivisor)) {
            maxScore = score;
            resultDivisor = divisor;
        }
    }

    return resultDivisor;
};