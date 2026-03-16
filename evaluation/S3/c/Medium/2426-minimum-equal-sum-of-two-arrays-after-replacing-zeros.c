// Source: https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays nums1 and nums2 consisting of positive integers.
//
// You have to replace all the 0's in both arrays with strictly positive integers such that the sum of elements of both arrays becomes equal.
//
// Return the minimum equal sum you can obtain, or -1 if it is impossible.
//
// Example:
// Input: nums1 = [3,2,0,1,0], nums2 = [6,5,0]
// Output: 12
// Explanation: We can replace 0's in the following way:
// - Replace the two 0's in nums1 with the values 2 and 4. The resulting array is nums1 = [3,2,2,1,4].
// - Replace the 0 in nums2 with the value 1. The resulting array is nums2 = [6,5,1].
// Both arrays have an equal sum of 12. It can be shown that it is the minimum sum we can obtain.
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	0 <= nums1[i], nums2[i] <= 106
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
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minSum(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    long long sum1 = 0, sum2 = 0;
    int zeroCount1 = 0, zeroCount2 = 0;

    for (int i = 0; i < nums1Size; i++) {
        if (nums1[i] == 0) {
            zeroCount1++;
        } else {
            sum1 += nums1[i];
        }
    }

    for (int i = 0; i < nums2Size; i++) {
        if (nums2[i] == 0) {
            zeroCount2++;
        } else {
            sum2 += nums2[i];
        }
    }

    long long maxSum = sum1 + sum2 + (long long)(zeroCount1 + zeroCount2) * 1000000;
    if (maxSum % 2 != 0) {
        return -1; // Cannot have an odd total sum split into two equal parts
    }

    long long target = maxSum / 2;

    if (target < sum1 || target < sum2) {
        return -1; // Target cannot be less than the current sums
    }

    return target;      
}
