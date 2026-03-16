// Source: https://leetcode.com/problems/count-special-integers/   |   Difficulty: Hard
//
// Problem Description:
// We call a positive integer special if all of its digits are distinct.
//
// Given a positive integer n, return the number of special integers that belong to the interval [1, n].
//
// Example:
// Input: n = 20
// Output: 19
// Explanation: All the integers from 1 to 20, except 11, are special. Thus, there are 19 special integers.
//
// Constraints:
// 1 <= n <= 2 * 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countSpecialNumbers(int n) {
        int digits[10];
        int len = 0;
        int temp = n;
        while (temp > 0) {
            digits[len++] = temp % 10;
            temp /= 10;
        }
        std::reverse(digits, digits + len);

        int dp[11][1 << 10];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (int i = 0; i < len; ++i) {
            for (int mask = 0; mask < (1 << 10); ++mask) {
                int limit = (mask & (1 << 10)) ? 9 : digits[i];
                for (int d = 0; d <= limit; ++d) {
                    if (i == 0 && d == 0) continue; // leading zero
                    if (mask & (1 << d)) continue; // digit already used
                    int newMask = mask | (1 << d);
                    if (d < limit) newMask |= (1 << 10); // mark as less than n
                    dp[i + 1][newMask] += dp[i][mask];
                }
            }
        }

        int result = 0;
        for (int mask = 0; mask < (1 << 10); ++mask) {
            result += dp[len][mask];
        }

        // Add numbers with fewer digits than n
        for (int d = 1; d < len; ++d) {
            int count = 9;
            for (int i = 1; i < d; ++i) {
                count *= (10 - i);
            }
            result += count;
        }

        return result;          
    }
};
