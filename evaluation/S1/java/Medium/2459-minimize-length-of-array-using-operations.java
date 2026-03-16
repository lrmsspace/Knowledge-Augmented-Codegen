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
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    public int minimumArrayLength(int[] nums) {
        int gcd = 0;
        for (int num : nums) {
            gcd = gcd(gcd, num);
            if (gcd == 1) {
                return 1;
            }
        }
        return nums.length % 2;         
    }
}
