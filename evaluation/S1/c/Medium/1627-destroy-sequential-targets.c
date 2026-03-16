// Source: https://leetcode.com/problems/destroy-sequential-targets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers, representing targets on a number line. You are also given an integer space.
//
// You have a machine which can destroy targets. Seeding the machine with some nums[i] allows it to destroy all targets with values that can be represented as nums[i] + c * space, where c is any non-negative integer. You want to destroy the maximum number of targets in nums.
//
// Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of targets.
//
// Example:
// Input: nums = [3,7,8,1,1,5], space = 2
// Output: 1
// Explanation: If we seed the machine with nums[3], then we destroy all targets equal to 1,3,5,7,9,... 
// In this case, we would destroy 5 total targets (all except for nums[2]). 
// It is impossible to destroy more than 5 targets, so we return nums[3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= space <= 109
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Chinese Remainder Theorem (number, recursion, mod-exp)
//   • When to use: When you need to find a unique integer solution that satisfies a system of linear congruences with pairwise coprime moduli. It is used to reconstruct a number from its remainders modulo several divisors.
//   • Idea: The Chinese Remainder Theorem (CRT) finds a unique solution x modulo the product of several pairwise coprime moduli, given a system of congruences. It typically involves computing modular inverses and combining solutions, with a complexity often dominated by modular exponentiation or extended Euclidean algorithm, usually O(N log M) or O(N log(max_modulus)).
//   • Invariants: The current combined solution 'x' satisfies 'x % m_i == a_i' for all congruences '(a_i, m_i)' processed so far.; The current combined modulus 'M' is the product of all individual moduli processed so far.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime.; Incorrectly calculating modular inverses.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int destroyTargets(int* nums, int numsSize, int space) {
    int remainder_count[100000] = {0};
    int remainder_min[100000];
    for (int i = 0; i < 100000; i++) {
        remainder_min[i] = 1000000001; // larger than max nums[i]
    }

    for (int i = 0; i < numsSize; i++) {
        int remainder = nums[i] % space;
        remainder_count[remainder]++;
        if (nums[i] < remainder_min[remainder]) {
            remainder_min[remainder] = nums[i];
        }
    }

    int max_count = 0;
    int result = 1000000001; // larger than max nums[i]

    for (int r = 0; r < space; r++) {
        if (remainder_count[r] > max_count) {
            max_count = remainder_count[r];
            result = remainder_min[r];
        } else if (remainder_count[r] == max_count) {
            if (remainder_min[r] < result) {
                result = remainder_min[r];
            }
        }
    }

    return result;      
}
