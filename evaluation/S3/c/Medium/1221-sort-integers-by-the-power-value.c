// Source: https://leetcode.com/problems/sort-integers-by-the-power-value/   |   Difficulty: Medium
//
// Problem Description:
// The power of an integer x is defined as the number of steps needed to transform x into 1 using the following steps:
//
//
// 	if x is even then x = x / 2
// 	if x is odd then x = 3 * x + 1
//
//
// For example, the power of x = 3 is 7 because 3 needs 7 steps to become 1 (3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1).
//
// Given three integers lo, hi and k. The task is to sort all integers in the interval [lo, hi] by the power value in ascending order, if two or more integers have the same power value sort them by ascending order.
//
// Return the kth integer in the range [lo, hi] sorted by the power value.
//
// Notice that for any integer x (lo <= x <= hi) it is guaranteed that x will transform into 1 using these steps and that the power of x is will fit in a 32-bit signed integer.
//
// Example:
// Input: lo = 12, hi = 15, k = 2
// Output: 13
// Explanation: The power of 12 is 9 (12 --> 6 --> 3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1)
// The power of 13 is 9
// The power of 14 is 17
// The power of 15 is 17
// The interval sorted by the power value [12,13,14,15]. For k = 2 answer is the second element which is 13.
// Notice that 12 and 13 have the same power value and we sorted them in ascending order. Same for 14 and 15.
//
// Constraints:
// 1 <= lo <= hi <= 1000
// 	1 <= k <= hi - lo + 1
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int getKth(int lo, int hi, int k) {
    int power[1001];
    power[1] = 0; // Base case: power of 1 is 0

    // Function to compute the power of an integer using memoization
    int computePower(int x) {
        if (power[x] != 0) {
            return power[x]; // Return cached value if already computed
        }
        if (x % 2 == 0) {
            power[x] = 1 + computePower(x / 2); // Even case
        } else {
            power[x] = 1 + computePower(3 * x + 1); // Odd case
        }
        return power[x];
    }

    // Compute the power for all integers in the range [lo, hi]
    for (int i = lo; i <= hi; i++) {
        computePower(i);
    }

    // Create an array of pairs (power, integer) for sorting
    int pairs[1000][2];
    for (int i = lo; i <= hi; i++) {
        pairs[i - lo][0] = power[i]; // Power value
        pairs[i - lo][1] = i; // Original integer
    }

    // Sort the pairs based on power value and then by integer value
    for (int i = 0; i < hi - lo + 1; i++) {
        for (int j = i + 1; j < hi - lo + 1; j++) {
            if (pairs[i][0] > pairs[j][0] || (pairs[i][0] == pairs[j][0] && pairs[i][1] > pairs[j][1])) {
                // Swap pairs[i] and pairs[j]
                int tempPower = pairs[i][0];
                int tempInt = pairs[i][1];
                pairs[i][0] = pairs[j][0];
                pairs[i][1] = pairs[j][1];
                pairs[j][0] = tempPower;
                pairs[j][1] = tempInt;
            }
        }
    }

    return pairs[k - 1][1]; // Return the k-th integer based on sorted order        
}
