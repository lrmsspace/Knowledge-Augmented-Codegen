// Source: https://leetcode.com/problems/count-the-number-of-powerful-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers start, finish, and limit. You are also given a 0-indexed string s representing a positive integer.
//
// A positive integer x is called powerful if it ends with s (in other words, s is a suffix of x) and each digit in x is at most limit.
//
// Return the total number of powerful integers in the range [start..finish].
//
// A string x is a suffix of a string y if and only if x is a substring of y that starts from some index (including 0) in y and extends to the index y.length - 1. For example, 25 is a suffix of 5125 whereas 512 is not.
//
// Example:
// Input: start = 1, finish = 6000, limit = 4, s = "124"
// Output: 5
// Explanation: The powerful integers in the range [1..6000] are 124, 1124, 2124, 3124, and, 4124. All these integers have each digit <= 4, and "124" as a suffix. Note that 5124 is not a powerful integer because the first digit is 5 which is greater than 4.
// It can be shown that there are only 5 powerful integers in this range.
//
// Constraints:
// 1 <= start <= finish <= 1015
// 	1 <= limit <= 9
// 	1 <= s.length <= floor(log10(finish)) + 1
// 	s only consists of numeric digits which are at most limit.
// 	s does not have leading zeros.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long countUpTo(long num, int limit, String s) {
        String numStr = Long.toString(num);
        int n = numStr.length();
        int m = s.length();
        long[][][] dp = new long[n + 1][2][2];
        dp[0][1][0] = 1; // position, tight, suffixMatched

        for (int i = 0; i < n; i++) {
            int digitLimit = (numStr.charAt(i) - '0');
            for (int tight = 0; tight <= 1; tight++) {
                for (int suffixMatched = 0; suffixMatched <= 1; suffixMatched++) {
                    long ways = dp[i][tight][suffixMatched];
                    if (ways == 0) continue;

                    int maxDigit = tight == 1 ? digitLimit : limit;
                    for (int digit = 0; digit <= maxDigit; digit++) {
                        int newTight = (tight == 1 && digit == digitLimit) ? 1 : 0;
                        int newSuffixMatched = suffixMatched;

                        if (i >= n - m) {
                            char expectedChar = s.charAt(i - (n - m));
                            if (digit == expectedChar - '0') {
                                newSuffixMatched = 1;
                            } else {
                                newSuffixMatched = 0;
                            }
                        }

                        dp[i + 1][newTight][newSuffixMatched] += ways;
                    }
                }
            }
        }

        return dp[n][0][1] + dp[n][1][1];
    }
    public long numberOfPowerfulInt(long start, long finish, int limit, String s) {
        return countUpTo(finish, limit, s) - countUpTo(start - 1, limit, s);            
    }
}
