// Source: https://leetcode.com/problems/palindrome-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer x, return true if x is a palindrome, and false otherwise.
//
// Example:
// Input: x = 121
// Output: true
// Explanation: 121 reads as 121 from left to right and from right to left.
//
// Constraints:
// -231 <= x <= 231 - 1
//
//
//  
// Follow up: Could you solve it without converting the integer to a string?
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Primality tests (number, mod-exp, randomized, probability-statistics, simulation)
//   • When to use: Use when needing to efficiently determine if a large number is prime or composite, especially for cryptographic applications or number theory problems. It's suitable for verifying primality with high probability, or deterministically for numbers within certain bounds.
//   • Idea: The Miller-Rabin primality test is a probabilistic algorithm that determines if a given number is composite or a strong probable prime. It leverages properties of modular arithmetic and Fermat's Little Theorem to achieve a polynomial time complexity, typically O(k * log^3 n) for k iterations.
//   • Invariants: The number `n` being tested is an odd integer greater than 2.; The expression `n-1` is decomposed into `2^s * d`, where `d` is an odd integer.
//   • Tips: Pre-check for small prime divisors to quickly filter out many composite numbers.; Perform multiple iterations with different random bases to increase the certainty of primality.
//   • Pitfalls: The probabilistic version can yield false positives (strong probable primes) if too few bases are tested.; Incorrectly implementing modular exponentiation can lead to incorrect results or performance issues.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isPalindrome(int x) {
        // Negative numbers and numbers ending with 0 (but not 0 itself) are not palindromes
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int reversedHalf = 0;
        while (x > reversedHalf) {
            int digit = x % 10;
            reversedHalf = reversedHalf * 10 + digit;
            x /= 10;
        }

        // For even length numbers, x should equal reversedHalf
        // For odd length numbers, x should equal reversedHalf without the middle digit
        return x == reversedHalf || x == reversedHalf / 10;         
    }
}
