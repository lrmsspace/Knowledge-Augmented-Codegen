// Source: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.
//
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,3], k = 2
// Output: 6
// Explanation: The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= 105
//

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long totalSubarrays = (long long)n * (n + 1) / 2;

        long long invalidSubarrays = 0;
        int left = 0;

        while (left < n) {
            if (nums[left] == k) {
                left++;
                continue;
            }

            int right = left;
            int maxInSegment = nums[left];
            int countOfMax = (nums[left] == maxInSegment) ? 1 : 0;

            while (right < n && nums[right] != k) {
                if (nums[right] > maxInSegment) {
                    maxInSegment = nums[right];
                    countOfMax = 1;
                } else if (nums[right] == maxInSegment) {
                    countOfMax++;
                }
                right++;
            }

            if (maxInSegment < k) {
                long long length = right - left;
                invalidSubarrays += (length * (length + 1)) / 2;
            } else if (countOfMax < 2) {
                long long length = right - left;
                invalidSubarrays += (length * (length + 1)) / 2;
            }

            left = right;
        }

        return totalSubarrays - invalidSubarrays;           
    }
};
