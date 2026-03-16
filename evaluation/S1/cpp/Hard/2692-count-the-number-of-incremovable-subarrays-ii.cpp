// Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums.
//
// A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.
//
// Return the total number of incremovable subarrays of nums.
//
// Note that an empty array is considered strictly increasing.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 10
// Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
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
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n), right(n);
        left[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                left[i] = left[i - 1] + 1;
            } else {
                left[i] = 1;
            }
        }
        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                right[i] = right[i + 1] + 1;
            } else {
                right[i] = 1;
            }
        }

        long long totalSubarrays = static_cast<long long>(n) * (n + 1) / 2;
        long long nonIncremovableCount = 0;

        for (int i = 0; i < n; ++i) {
            long long leftCount = left[i];
            long long rightCount = right[i];
            nonIncremovableCount += leftCount * rightCount - 1;
        }

        return totalSubarrays - nonIncremovableCount;           
    }
};
