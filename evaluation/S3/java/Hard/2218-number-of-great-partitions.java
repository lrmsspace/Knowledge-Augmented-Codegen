// Source: https://leetcode.com/problems/number-of-great-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of positive integers and an integer k.
//
// Partition the array into two ordered groups such that each element is in exactly one group. A partition is called great if the sum of elements of each group is greater than or equal to k.
//
// Return the number of distinct great partitions. Since the answer may be too large, return it modulo 109 + 7.
//
// Two partitions are considered distinct if some element nums[i] is in different groups in the two partitions.
//
// Example:
// Input: nums = [1,2,3,4], k = 4
// Output: 6
// Explanation: The great partitions are: ([1,2,3], [4]), ([1,3], [2,4]), ([1,4], [2,3]), ([2,3], [1,4]), ([2,4], [1,3]) and ([4], [1,2,3]).
//
// Constraints:
// 1 <= nums.length, k <= 1000
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countPartitions(int[] nums, int k) {
        int mod = (int) 1e9 + 7;
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum < 2 * k) {
            return 0;
        }
        int n = nums.length;
        int maxSum = sum - k;
        int[] dp = new int[maxSum + 1];
        dp[0] = 1; // Base case: There's one way to achieve a sum of 0 (using no elements)

        for (int num : nums) {
            for (int j = maxSum; j >= num; j--) {
                dp[j] = (dp[j] + dp[j - num]) % mod;
            }
        }

        // The number of ways to partition the array into two groups with sums >= k
        // is the total number of subsets minus the subsets that sum to less than k.
        int result = 0;
        for (int j = k; j <= maxSum; j++) {
            result = (result + dp[j]) % mod;
        }
        
        // Each valid partition is counted twice (once for each group), so we multiply by 2.
        return (result * 2) % mod;          
    }
}
