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
// - N/A
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
        int n = nums1.size();
        vector<long long> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = nums1[i] - nums2[i];
        }

        long long count = 0;
        mergeSort(arr, 0, n - 1, diff, count);
        return count;           
    }
};
