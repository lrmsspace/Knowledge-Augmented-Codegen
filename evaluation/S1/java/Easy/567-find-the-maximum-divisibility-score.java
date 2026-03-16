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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxDivScore(int[] nums, int[] divisors) {
        int maxScore = -1;
        int resultDivisor = -1;

        for (int divisor : divisors) {
            int currentScore = 0;

            for (int num : nums) {
                if (num % divisor == 0) {
                    currentScore++;
                }
            }

            if (currentScore > maxScore || (currentScore == maxScore && divisor < resultDivisor)) {
                maxScore = currentScore;
                resultDivisor = divisor;
            }
        }

        return resultDivisor;           
    }
}
