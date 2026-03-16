// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, m and k, and an integer array nums.
// A sequence of integers seq is called magical if:
//
//
// 	seq has a size of m.
// 	0 <= seq[i] < nums.length
// 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
//
//
// The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
//
// Return the sum of the array products for all valid magical sequences.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A set bit refers to a bit in the binary representation of a number that has a value of 1.
//
// Example:
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
//
// Output: 991600007
//
// Explanation:
//
// All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
//
// Constraints:
// 1 <= k <= m <= 30
// 	1 <= nums.length <= 50
// 	1 <= nums[i] <= 108
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int magicalSum(int m, int k, int* nums, int numsSize) {
    // The maximum possible value of 2^seq[0] + 2^seq[1] + ... + 2^seq[m - 1] is when seq contains the largest indices, which is 2^(numsSize - 1) + 2^(numsSize - 2) + ... + 2^(numsSize - m). This can be simplified to (2^numsSize - 1) - (2^(numsSize - m) - 1) = 2^numsSize - 2^(numsSize - m).
    // We need to count how many magical sequences have a sum of powers of two that has exactly k set bits. This is equivalent to counting how many ways we can choose m indices from nums such that the sum of their corresponding powers of two has k set bits.
    // We can use a bitmask to represent the chosen indices and count the number of set bits in the resulting sum of powers of two.
    // We can iterate through all possible combinations of indices and check if the sum of their corresponding powers of two has k set bits. If it does, we calculate the product of the corresponding nums values and add it to our result.

    int mod = 1000000007;
    long long result = 0;

    // There are at most C(numsSize, m) combinations, which is manageable for numsSize <= 50 and m <= 30.
    for (int i = 0; i < (1 << numsSize); i++) {
        if (__builtin_popcount(i) == m) { // Check if we have chosen exactly m indices
            int sum_of_powers = 0;
            long long product = 1;
            for (int j = 0; j < numsSize; j++) {
                if (i & (1 << j)) { // If the j-th index is chosen
                    sum_of_powers += (1 << j); // Add the power of two corresponding to this index
                    product = (product * nums[j]) % mod; // Update the product
                }
            }
            if (__builtin_popcount(sum_of_powers) == k) { // Check if the sum of powers has k set bits
                result = (result + product) % mod; // Add to result
            }
        }
    }

    return (int)result;     
}
