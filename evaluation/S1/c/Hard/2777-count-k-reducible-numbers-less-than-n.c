// Source: https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s representing a number n in its binary form.
//
// You are also given an integer k.
//
// An integer x is called k-reducible if performing the following operation at most k times reduces it to 1:
//
//
// 	Replace x with the count of set bits in its binary representation.
//
//
// For example, the binary representation of 6 is "110". Applying the operation once reduces it to 2 (since "110" has two set bits). Applying the operation again to 2 (binary "10") reduces it to 1 (since "10" has one set bit).
//
// Return an integer denoting the number of positive integers less than n that are k-reducible.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "111", k = 1
//
// Output: 3
//
// Explanation: 
//
// n = 7. The 1-reducible integers less than 7 are 1, 2, and 4.
//
// Constraints:
// 1 <= s.length <= 800
// 	s has no leading zeros.
// 	s consists only of the characters '0' and '1'.
// 	1 <= k <= 5
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Bit manipulation (number, counting, recursion)
//   • When to use: Use for efficient low-level operations on integers, checking properties related to powers of two, or manipulating individual bits. It provides constant-time solutions for many numerical checks.
//   • Idea: This card covers fundamental bitwise operations for checking number properties like divisibility by powers of two, identifying powers of two, and manipulating individual bits. These operations typically run in O(1) time complexity.
//   • Invariants: For a positive integer `n`, `(n & (n - 1)) == 0` if and only if `n` is a power of two.; An integer `n` is divisible by `2^k` if and only if its `k` least significant bits are all zero, which is checked by `(n & ((1 << k) - 1)) == 0`.
//   • Tips: Use `n & 1` to efficiently check if a number `n` is odd or even.; The expression `1 << k` calculates 2 raised to the power of `k`.
//   • Pitfalls: When checking if a number is a power of two, remember to handle the `n == 0` case separately as `0 & (-1)` is `0`.; Be cautious with integer overflow when performing left shifts (`1 << k`) for large `k` values.
// - Discrete Root
//  (number, gcd, mod-exp)
//   • When to use: Used to find all solutions to a discrete root problem of the form x^k 
//  a mod n, given one solution and a primitive root g for the modulus n.
//   • Idea: This algorithm finds all solutions to a discrete root congruence x^k a mod n by leveraging properties of primitive roots and Euler's totient function phi(n).
//   • Invariants: The base g is a primitive root modulo n.; The exponent y_0 + i * (phi(n) / gcd(k, phi(n))) is always an integer for valid i.
//   • Tips: Ensure the base g is indeed a primitive root modulo n.; Accurately calculate Euler's totient function phi(n).
//   • Pitfalls: Assuming g is a primitive root when it is not, leading to incorrect results.; Errors in calculating phi(n) or gcd(k, phi(n)).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countKReducibleNumbers(char* s, int k) {
    /* Precompute the number of steps to reduce i to 1 */
    int maxBits = 800; /* max length of s */
    int steps[ maxBits + 1];
    steps[0] = -1; /* invalid */
    steps[1] = 0;
    for (int i = 2; i <= maxBits; ++i) {
        int cnt = 0, x = i;
        while (x != 1) {
            int setBits = 0;
            for (int b = 0; b < maxBits; ++b) {
                if (x & (1 << b)) ++setBits;
            }
            x = setBits;
            ++cnt;
        }
        steps[i] = cnt;
    }

    /* Count valid numbers less than n with digit DP */
    int len = strlen(s);
    int dp[len + 1][len + 1]; /* dp[pos][sum] */
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int pos = 0; pos < len; ++pos) {
        int limit = (s[pos] == '1') ? 1 : 0;
        for (int sum = 0; sum <= pos; ++sum) {
            for (int digit = 0; digit <= limit; ++digit) {
                dp[pos + 1][sum + digit] += dp[pos][sum];
            }
        }
    }

    /* Sum up counts for sums that reduce to 1 in k steps */
    int MOD = 1000000007;
    int result = 0;
    for (int sum = 1; sum <= len; ++sum) {
        if (steps[sum] == k - 1) { /* k-reducible means steps to 1 is k-1 */
            result = (result + dp[len][sum]) % MOD;
        }
    }

    /* Adjust for the case when k == 1 (exclude '1' itself) */
    if (k == 1) {
        result = (result - 1 + MOD) % MOD;
    }

    return result;      
}
