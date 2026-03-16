// Source: https://leetcode.com/problems/harshad-number/   |   Difficulty: Easy
//
// Problem Description:
// An integer divisible by the sum of its digits is said to be a Harshad number. You are given an integer x. Return the sum of the digits of x if x is a Harshad number, otherwise, return -1.
//
// Example:
// Input: x = 18
//
// Output: 9
//
// Explanation:
//
// The sum of digits of x is 9. 18 is divisible by 9. So 18 is a Harshad number and the answer is 9.
//
// Constraints:
// 1 <= x <= 100
//
// Helpful references (internal KB):
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Linear Congruence Equation (number, gcd, mod-exp, enumeration)
//   • When to use: Use when solving equations of the form ax 
//  b (mod n) for x. It determines existence, finds unique solutions when a and n are coprime, or enumerates all solutions otherwise.
//   • Idea: This algorithm finds solutions to linear congruence equations ax b (mod n) by leveraging properties of the greatest common divisor.
//   • Invariants: The congruence ax 
//  b (mod n) holds for any valid solution x.; The original equation has solutions if and only if b is divisible by gcd(a, n).
//   • Tips: Always calculate gcd(a, n) first to determine solution existence and count.; Check if b is divisible by gcd(a, n); if not, no solutions exist.
//   • Pitfalls: Forgetting to check divisibility of b by gcd(a, n) can lead to incorrect solution attempts.; Incorrectly assuming a unique solution when a and n are not coprime.
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
    public int sumOfTheDigitsOfHarshadNumber(int x) {
        int sumOfDigits = 0;
        int temp = x;

        while (temp > 0) {
            sumOfDigits += temp % 10;
            temp /= 10;
        }

        if (x % sumOfDigits == 0) {
            return sumOfDigits;
        } else {
            return -1;
        }           
    }
}
