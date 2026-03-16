// Source: https://leetcode.com/problems/count-number-of-nice-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
//
// Return the number of nice sub-arrays.
//
// Example:
// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
//
// Constraints:
// 1 <= nums.length <= 50000
// 	1 <= nums[i] <= 10^5
// 	1 <= k <= nums.length
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
    int numberOfSubarrays(vector<int>& nums, int k) {
        int count = 0;
        int left = 0;
        int oddCount = 0;

        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] % 2 == 1) {
                ++oddCount;
            }

            while (oddCount > k) {
                if (nums[left] % 2 == 1) {
                    --oddCount;
                }
                ++left;
            }

            if (oddCount == k) {
                int tempLeft = left;
                while (tempLeft < right && nums[tempLeft] % 2 == 0) {
                    ++tempLeft;
                }
                count += tempLeft - left + 1;
            }
        }

        return count;           
    }
};
