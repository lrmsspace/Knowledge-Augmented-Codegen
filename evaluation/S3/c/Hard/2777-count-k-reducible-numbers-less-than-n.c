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
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countKReducibleNumbers(char* s, int k) {
    // Implementing a digit DP approach to count k-reducible numbers less than n.
    // The idea is to count how many numbers less than n have a certain number of set bits,
    // and then determine how many of those are k-reducible.

    // Step 1: Convert the binary string s to an integer n.
    int n = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        n = n * 2 + (s[i] - '0');
    }

    // Step 2: Precompute the number of set bits for all numbers up to n.
    int setBitsCount[800]; // We can store counts for numbers up to 800 (since s.length <= 800).
    for (int i = 0; i < 800; i++) {
        setBitsCount[i] = __builtin_popcount(i); // Count set bits using built-in function.
    }

    // Step 3: Use a DP approach to count how many numbers less than n have a certain number of set bits.
    int dp[800][6]; // dp[i][j] will store the count of numbers with j set bits up to i.
    for (int i = 0; i < 800; i++) {
        for (int j = 0; j <= 5; j++) {
            dp[i][j] = 0;
        }
        dp[i][setBitsCount[i]]++;
    }

    // Step 4: Calculate the cumulative counts for each number of set bits.
    for (int j = 0; j <= 5; j++) {
        for (int i = 1; i < 800; i++) {
            dp[i][j] += dp[i - 1][j];
        }
    }

    // Step 5: Count k-reducible numbers less than n.
    int result = 0;
    for (int j = 1; j <= 5; j++) { // We only care about numbers with at least one set bit.
        if (j <= k) {
            result += dp[n - 1][j]; // Count numbers with j set bits less than n.
        }
    }

    return result % (1000000007); // Return the result modulo 10^9 + 7.     
}
