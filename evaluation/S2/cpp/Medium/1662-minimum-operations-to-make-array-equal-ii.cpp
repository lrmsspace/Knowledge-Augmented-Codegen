// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of equal length n and an integer k. You can perform the following operation on nums1:
//
//
// 	Choose two indexes i and j and increment nums1[i] by k and decrement nums1[j] by k. In other words, nums1[i] = nums1[i] + k and nums1[j] = nums1[j] - k.
//
//
// nums1 is said to be equal to nums2 if for all indices i such that 0 <= i < n, nums1[i] == nums2[i].
//
// Return the minimum number of operations required to make nums1 equal to nums2. If it is impossible to make them equal, return -1.
//
// Example:
// Input: nums1 = [4,3,1,4], nums2 = [1,3,7,1], k = 3
// Output: 2
// Explanation: In 2 operations, we can transform nums1 to nums2.
// 1st operation: i = 2, j = 0. After applying the operation, nums1 = [1,3,4,4].
// 2nd operation: i = 2, j = 3. After applying the operation, nums1 = [1,3,7,1].
// One can prove that it is impossible to make arrays equal in fewer operations.
//
// Constraints:
// n == nums1.length == nums2.length
// 	2 <= n <= 105
// 	0 <= nums1[i], nums2[j] <= 109
// 	0 <= k <= 105
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
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        long long operations = 0;
        long long sum1 = 0, sum2 = 0;

        for (size_t i = 0; i < nums1.size(); ++i) {
            if (nums1[i] >= nums2[i]) {
                if ((nums1[i] - nums2[i]) % k != 0) {
                    return -1;
                }
                operations += (nums1[i] - nums2[i]) / k;
            } else {
                if ((nums2[i] - nums1[i]) % k != 0) {
                    return -1;
                }
                operations -= (nums2[i] - nums1[i]) / k;
            }
            sum1 += nums1[i];
            sum2 += nums2[i];
        }

        if (sum1 != sum2) {
            return -1;
        }

        return operations >= 0 ? operations : -operations;          
    }
};
