// Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and m that consist of the same number of digits.
//
// You can perform the following operations any number of times:
//
//
// 	Choose any digit from n that is not 9 and increase it by 1.
// 	Choose any digit from n that is not 0 and decrease it by 1.
//
//
// The integer n must not be a prime number at any point, including its original value and after each operation.
//
// The cost of a transformation is the sum of all values that n takes throughout the operations performed.
//
// Return the minimum cost to transform n into m. If it is impossible, return -1.
//
// Example:
// Input: n = 10, m = 12
//
// Output: 85
//
// Explanation:
//
// We perform the following operations:
//
//
// 	Increase the first digit, now n = 20.
// 	Increase the second digit, now n = 21.
// 	Increase the second digit, now n = 22.
// 	Decrease the first digit, now n = 12.
//
// Constraints:
// 1 <= n, m < 104
// 	n and m consist of the same number of digits.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minOperations(int n, int m) {
        // Step 1: Check if n and m have the same number of digits
        String strN = Integer.toString(n);
        String strM = Integer.toString(m);
        if (strN.length() != strM.length()) {
            return -1; // Impossible if they don't have the same number of digits
        }

        // Step 2: Check if n is prime
        if (isPrime(n)) {
            return -1; // Impossible if n is prime at the start
        }

        int cost = 0;
        int current = n;

        // Step 3: Transform n to m
        for (int i = 0; i < strN.length(); i++) {
            int digitN = strN.charAt(i) - '0';
            int digitM = strM.charAt(i) - '0';

            while (digitN != digitM) {
                if (digitN < digitM) {
                    digitN++;
                } else {
                    digitN--;
                }
                current = updateDigit(current, i, digitN);
                cost += current;

                // Check if current is prime after each operation
                if (isPrime(current)) {
                    return -1; // Impossible if current becomes prime at any point
                }
            }
        }

        return cost;            
    }
}
