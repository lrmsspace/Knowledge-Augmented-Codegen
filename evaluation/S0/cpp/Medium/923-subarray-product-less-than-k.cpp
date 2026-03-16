// Source: https://leetcode.com/problems/subarray-product-less-than-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.
//
// Example:
// Input: nums = [10,5,2,6], k = 100
// Output: 8
// Explanation: The 8 subarrays that have product less than 100 are:
// [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
// Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	1 <= nums[i] <= 1000
// 	0 <= k <= 106
//

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;

        int left = 0;
        int right = 0;
        int count = 0;
        long long product = 1;

        while (right < nums.size()) {
            product *= nums[right];

            while (product >= k) {
                product /= nums[left];
                left++;
            }

            count += right - left + 1;
            right++;
        }

        return count;           
    }
};
