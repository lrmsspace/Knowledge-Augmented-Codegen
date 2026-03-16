// Source: https://leetcode.com/problems/longest-increasing-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// Find the longest subsequence of nums that meets the following requirements:
//
//
// 	The subsequence is strictly increasing and
// 	The difference between adjacent elements in the subsequence is at most k.
//
//
// Return the length of the longest subsequence that meets the requirements.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [4,2,1,4,3,4,5,8,15], k = 3
// Output: 5
// Explanation:
// The longest subsequence that meets the requirements is [1,3,4,5,8].
// The subsequence has a length of 5, so we return 5.
// Note that the subsequence [1,3,4,5,8,15] does not meet the requirements because 15 - 8 = 7 is larger than 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 105
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int lengthOfLIS(int* nums, int numsSize, int k) {
    /* Segment tree for range maximum query and point update */
    #define ST_SIZE 131072 /* >= 2^17 to cover nums[i] up to 10^5 */
    int segtree[ST_SIZE * 2] = {0};

    /* Update position pos (1-based) with value val */
    void segtree_update(int pos, int val) {
        pos += ST_SIZE - 1;
        if (segtree[pos] >= val) return; /* no need to update */
        segtree[pos] = val;
        while (pos > 1) {
            pos /= 2;
            int left = segtree[pos * 2];
            int right = segtree[pos * 2 + 1];
            segtree[pos] = (left > right) ? left : right;
        }
    }

    /* Query maximum in range [l, r] (1-based, inclusive) */
    int segtree_query(int l, int r) {
        int res = 0;
        l += ST_SIZE - 1;
        r += ST_SIZE - 1;
        while (l <= r) {
            if ((l & 1) == 1) {
                if (segtree[l] > res) res = segtree[l];
                l++;
            }
            if ((r & 1) == 0) {
                if (segtree[r] > res) res = segtree[r];
                r--;
            }
            l /= 2; r /= 2;
        }
        return res;
    }

    int maxLen = 0;
    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        int left = (val - k > 1) ? (val - k) : 1;
        int right = val - 1;
        int bestPrev = (left <= right) ? segtree_query(left, right) : 0;
        int currLen = bestPrev + 1;
        segtree_update(val, currLen);
        if (currLen > maxLen) maxLen = currLen;
    }
    return maxLen;      
}
