// Source: https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:
//
//
// 	The length of the subarray is k, and
// 	All the elements of the subarray are distinct.
//
//
// Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return 0.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,5,4,2,9,9,9], k = 3
// Output: 15
// Explanation: The subarrays of nums with length 3 are:
// - [1,5,4] which meets the requirements and has a sum of 10.
// - [5,4,2] which meets the requirements and has a sum of 11.
// - [4,2,9] which meets the requirements and has a sum of 15.
// - [2,9,9] which does not meet the requirements because the element 9 is repeated.
// - [9,9,9] which does not meet the requirements because the element 9 is repeated.
// We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

long long maximumSubarraySum(int* nums, int numsSize, int k) {
    long long max_sum = 0, curr_sum = 0;
    int count[100001] = {0};
    int distinct_count = 0;

    for (int i = 0; i < numsSize; i++) {
        curr_sum += nums[i];
        count[nums[i]]++;
        if (count[nums[i]] == 1) {
            distinct_count++;
        }

        if (i >= k) {
            curr_sum -= nums[i - k];
            count[nums[i - k]]--;
            if (count[nums[i - k]] == 0) {
                distinct_count--;
            }
        }

        if (i >= k - 1 && distinct_count == k) {
            if (curr_sum > max_sum) {
                max_sum = curr_sum;
            }
        }
    }

    return max_sum;     
}
