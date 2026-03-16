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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long countGoodIntegers(int n, int k) {
        const int MOD = 1e9 + 7;
        // dp[pos][mod][mask] = number of ways to fill first 'pos' digits
        // with sum % k == mod and digit parity mask
        long long dp[11][10][1024] = {};
        dp[0][0][0] = 1;

        for (int pos = 0; pos < n; ++pos) {
            for (int mod = 0; mod < k; ++mod) {
                for (int mask = 0; mask < 1024; ++mask) {
                    for (int digit = 0; digit <= 9; ++digit) {
                        if (pos == 0 && digit == 0) continue; // no leading zeros
                        int newMod = (mod + digit) % k;
                        int newMask = mask ^ (1 << digit);
                        dp[pos + 1][newMod][newMask] = (dp[pos + 1][newMod][newMask] + dp[pos][mod][mask]) % MOD;
                    }
                }
            }
        }

        long long result = 0;
        for (int mask = 0; mask < 1024; ++mask) {
            int oddCount = 0;
            for (int d = 0; d <= 9; ++d) {
                if (mask & (1 << d)) oddCount++;
            }
            // For even length n, all digits must have even counts
            // For odd length n, only one digit can have an odd count
            if ((n % 2 == 0 && oddCount == 0) || (n % 2 == 1 && oddCount == 1)) {
                result = (result + dp[n][0][mask]) % MOD;
            }
        }

        return result;          
    }
};
