// Source: https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums of non-negative integers, and two integers l and r.
//
// Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.
//
// Note that:
//
//
// 	Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
// 	The sum of an empty multiset is 0.
//
// Example:
// Input: nums = [1,2,2,3], l = 6, r = 6
// Output: 1
// Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	0 <= nums[i] <= 2 * 104
// 	Sum of nums does not exceed 2 * 104.
// 	0 <= l <= r <= 2 * 104
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSubMultisets(int* nums, int numsSize, int l, int r) {
    // The maximum possible sum of elements in nums is 2 * 10^4, which is manageable for a DP approach.
    // We can use a dynamic programming technique to count the number of sub-multisets with sums up to r and l-1, then take the difference.

    int max_sum = 20000; // Given in constraints
    int mod = 1000000007;

    // Create a frequency array to count occurrences of each number in nums
    int freq[max_sum + 1];
    for (int i = 0; i <= max_sum; i++) {
        freq[i] = 0;
    }
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Create a DP array where dp[i] will store the count of sub-multisets with sum i
    int dp[max_sum + 1];
    dp[0] = 1; // There's one way to have a sum of 0: the empty set
    for (int i = 1; i <= max_sum; i++) {
        dp[i] = 0;
    }

    // Fill the DP array using the frequency counts
    for (int num = 0; num <= max_sum; num++) {
        if (freq[num] > 0) {
            // For each number, we can use it from 1 to freq[num] times
            for (int j = max_sum; j >= num; j--) {
                for (int k = 1; k <= freq[num] && k * num <= j; k++) {
                    dp[j] = (dp[j] + dp[j - k * num]) % mod;
                }
            }
        }
    }

    // Calculate the count of sub-multisets with sum in [l, r]
    int count_r = 0;
    for (int i = l; i <= r && i <= max_sum; i++) {
        count_r = (count_r + dp[i]) % mod;
    }

    return count_r;     
}
