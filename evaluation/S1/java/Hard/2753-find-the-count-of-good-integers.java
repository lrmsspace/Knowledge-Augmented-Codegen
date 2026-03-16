// Source: https://leetcode.com/problems/find-the-count-of-good-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// An integer is called good if its digits can be rearranged to form a k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.
//
// Return the count of good integers containing n digits.
//
// Note that any integer must not have leading zeros, neither before nor after rearrangement. For example, 1010 cannot be rearranged to form 101.
//
// Example:
// Input: n = 3, k = 5
//
// Output: 27
//
// Explanation:
//
// Some of the good integers are:
//
//
// 	551 because it can be rearranged to form 515.
// 	525 because it is already k-palindromic.
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 9
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative or positive integer solutions to a linear equation of sums.
//   • Idea: A combinatorial technique to count the number of ways to distribute 'n' identical items into 'k' distinct bins, or find integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout the distribution.; The number of 'bars' (dividers, k-1) remains constant, separating the k distinct bins.
//   • Tips: Distinguish between non-negative (xi >= 0) and positive (xi >= 1) integer solutions; the latter requires a variable transformation.; For positive integer solutions (xi >= 1), transform variables to yi = xi - 1, then solve for yi >= 0 with a reduced sum.
//   • Pitfalls: Confusing identical items/distinct bins with distinct items/distinct bins (which is k^n).; Incorrectly applying the formula for positive vs. non-negative constraints without transformation.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long modInverse(long a, long mod) {
        long m0 = mod, t, q;
        long x0 = 0, x1 = 1;

        if (mod == 1) return 0;

        while (a > 1) {
            q = a / mod;
            t = mod;

            mod = a % mod;
            a = t;
            t = x0;

            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0) x1 += m0;

        return x1;
    }
    private long nCrMod(int n, int r, long mod) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;

        long[] fact = new long[n + 1];
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        long numerator = fact[n];
        long denominator = (fact[r] * fact[n - r]) % mod;

        return (numerator * modInverse(denominator, mod)) % mod;
    }
    public long countGoodIntegers(int n, int k) {
        long mod = 1_000_000_007;
        long result = 0;

        // Iterate through all possible digit counts (0-9)
        for (int digit = 0; digit <= 9; digit++) {
            // Check if the digit is divisible by k
            if (digit % k != 0) continue;

            // Calculate the maximum pairs we can form with n digits
            int maxPairs = n / 2;
            for (int pairs = 0; pairs <= maxPairs; pairs++) {
                int singles = n - 2 * pairs;

                // Check if the current configuration can form a palindrome
                if ((singles > 0 && digit == 0) || (singles == 0 && n % 2 == 1)) {
                    continue; // Leading zero or odd length without singles
                }

                // Calculate combinations using stars and bars
                long combinations = nCrMod(n - (singles > 0 ? 1 : 0), pairs, mod);
                result = (result + combinations) % mod;
            }
        }

        return result;          
    }
}
