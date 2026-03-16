// Source: https://leetcode.com/problems/number-of-pairs-satisfying-inequality/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and an integer diff. Find the number of pairs (i, j) such that:
//
//
// 	0 <= i < j <= n - 1 and
// 	nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
//
//
// Return the number of pairs that satisfy the conditions.
//
// Example:
// Input: nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
// Output: 3
// Explanation:
// There are 3 pairs that satisfy the conditions:
// 1. i = 0, j = 1: 3 - 2 <= 2 - 2 + 1. Since i < j and 1 <= 1, this pair satisfies the conditions.
// 2. i = 0, j = 2: 3 - 5 <= 2 - 1 + 1. Since i < j and -2 <= 2, this pair satisfies the conditions.
// 3. i = 1, j = 2: 2 - 5 <= 2 - 1 + 1. Since i < j and -3 <= 2, this pair satisfies the conditions.
// Therefore, we return 3.
//
// Constraints:
// n == nums1.length == nums2.length
// 	2 <= n <= 105
// 	-104 <= nums1[i], nums2[i] <= 104
// 	-104 <= diff <= 104
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: Use when frequent point updates and range sum queries are needed on an array. It offers logarithmic time complexity for both operations, making it more efficient than a simple prefix sum array for dynamic data.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently calculates prefix sums and updates individual elements in an array. Both operations typically run in O(log N) time.
//   • Invariants: Each node `tree[i]` stores the sum of a specific range of elements ending at index `i`.; The length of the range summed by `tree[i]` is determined by `i & (-i)` (lowbit operation).
//   • Tips: Understand the lowbit operation and its role in navigating the tree structure.; Use 1-based indexing for simpler implementation of lowbit calculations.
//   • Pitfalls: Forgetting 1-based indexing can lead to off-by-one errors and incorrect results.; Incorrectly implementing the lowbit calculation or update/query logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        int n = (int)nums1.size();
        vector<long long> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = (long long)nums1[i] - (long long)nums2[i];
        }

        // Count pairs (i, j) where i < j and arr[i] <= arr[j] + diff
        long long count = 0;
        FenwickTree fenw(n);
        vector<long long> sortedArr(arr);
        sort(sortedArr.begin(), sortedArr.end());

        for (int i = 0; i < n; ++i) {
            // Find the number of elements in fenw that are <= arr[i] + diff
            long long target = arr[i] + diff;
            int idx = upper_bound(sortedArr.begin(), sortedArr.end(), target) - sortedArr.begin();
            count += fenw.query(idx); // Count how many have been added that are <= target
            // Add current element to fenw
            int updateIdx = lower_bound(sortedArr.begin(), sortedArr.end(), arr[i]) - sortedArr.begin() + 1;
            fenw.update(updateIdx, 1); // Mark this element as seen
        }

        return count;           
    }
};
