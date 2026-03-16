// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num which represents a positive integer, and an integer t.
//
// A number is called zero-free if none of its digits are 0.
//
// Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
//
// Example:
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// Constraints:
// 2 <= num.length <= 2 * 105
// 	num consists only of digits in the range ['0', '9'].
// 	num does not contain leading zeros.
// 	1 <= t <= 1014
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean digitDP(String num, int[] primeFactors, StringBuilder result, int index, boolean tight) {
        if (index == num.length()) {
            for (int count : primeFactors) {
                if (count > 0) {
                    return false; // Not all prime factors are used
                }
            }
            return true; // Valid number formed
        }

        int limit = tight ? (num.charAt(index) - '0') : 9;
        for (int digit = 1; digit <= limit; digit++) {
            // Update prime factors
            int[] newPrimeFactors = Arrays.copyOf(primeFactors, primeFactors.length);
            int tempDigit = digit;
            for (int prime : new int[]{2, 3, 5, 7}) {
                while (tempDigit % prime == 0) {
                    newPrimeFactors[prime]--;
                    tempDigit /= prime;
                }
            }

            boolean canForm = digitDP(num, newPrimeFactors, result, index + 1, tight && (digit == limit));
            if (canForm) {
                result.append(digit);
                return true;
            }
        }
        return false; // No valid digit found
    }
    public String smallestNumber(String num, long t) {
        // Handle special cases for t
        if (t == 1) {
            return num; // Any number's digit product is divisible by 1
        }
        if (t == 0) {
            return "-1"; // No zero-free number can have a product divisible by 0
        }

        // Factor t into its prime factors
        long originalT = t;
        int[] primeFactors = new int[10]; // Store counts of prime factors 2,3,5,7
        int[] primes = {2, 3, 5, 7};
        for (int i = 0; i < primes.length; i++) {
            while (t % primes[i] == 0) {
                primeFactors[primes[i]]++;
                t /= primes[i];
            }
        }
        if (t > 1) {
            return "-1"; // t has prime factors greater than 7
        }

        // Use Digit DP to find the smallest valid number
        int n = num.length();
        StringBuilder result = new StringBuilder();
        if (!digitDP(num, primeFactors, result, 0, true)) {
            return "-1";
        }
        return result.toString();           
    }
}
