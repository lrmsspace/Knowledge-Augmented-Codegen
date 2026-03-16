// Source: https://leetcode.com/problems/maximum-69-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num consisting only of digits 6 and 9.
//
// Return the maximum number you can get by changing at most one digit (6 becomes 9, and 9 becomes 6).
//
// Example:
// Input: num = 9669
// Output: 9969
// Explanation: 
// Changing the first digit results in 6669.
// Changing the second digit results in 9969.
// Changing the third digit results in 9699.
// Changing the fourth digit results in 9666.
// The maximum number is 9969.
//
// Constraints:
// 1 <= num <= 104
// 	num consists of only 6 and 9 digits.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Integer factorization (number, enumeration)
//   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
//   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
//   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
//   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
//   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximum69Number (int num) {
        int multiplier = 1;
        int result = num;
        bool changed = false;

        while (num > 0) {
            int digit = num % 10;
            if (digit == 6 && !changed) {
                result += 3 * multiplier;  // Change 6 to 9
                changed = true;
            }
            num /= 10;
            multiplier *= 10;
        }

        return result;          
    }
};
