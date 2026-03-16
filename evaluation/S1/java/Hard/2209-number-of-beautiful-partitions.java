// Source: https://leetcode.com/problems/number-of-beautiful-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
//
// A partition of s is called beautiful if:
//
//
// 	s is partitioned into k non-intersecting substrings.
// 	Each substring has a length of at least minLength.
// 	Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
//
//
// Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "23542185131", k = 3, minLength = 2
// Output: 3
// Explanation: There exists three ways to create a beautiful partition:
// "2354 | 218 | 5131"
// "2354 | 21851 | 31"
// "2354218 | 51 | 31"
//
// Constraints:
// 1 <= k, minLength <= s.length <= 1000
// 	s consists of the digits '1' to '9'.
//
// Helpful references (internal KB):
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isPrime(char ch) {
        return ch == '2' || ch == '3' || ch == '5' || ch == '7';
    }
    public int beautifulPartitions(String s, int k, int minLength) {
        int n = s.length();
        int MOD = 1_000_000_007;

        boolean isPrimeStart = isPrime(s.charAt(0));
        boolean isNonPrimeEnd = !isPrime(s.charAt(n - 1));
        if (!isPrimeStart || !isNonPrimeEnd) {
            return 0;
        }

        int[] dp = new int[n + 1];
        dp[0] = 1;

        for (int part = 1; part <= k; part++) {
            int[] newDp = new int[n + 1];
            int prefixSum = 0;

            for (int i = minLength; i <= n; i++) {
                if (!isPrime(s.charAt(i - minLength))) {
                    prefixSum = (prefixSum + dp[i - minLength]) % MOD;
                }
                if (isNonPrime(s.charAt(i - 1))) {
                    newDp[i] = prefixSum;
                }
            }
            dp = newDp;
        }

        return dp[n];           
    }
}
