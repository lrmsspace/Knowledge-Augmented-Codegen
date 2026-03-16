// Source: https://leetcode.com/problems/maximum-sum-of-almost-unique-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two positive integers m and k.
//
// Return the maximum sum out of all almost unique subarrays of length k of nums. If no such subarray exists, return 0.
//
// A subarray of nums is almost unique if it contains at least m distinct elements.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,6,7,3,1,7], m = 3, k = 4
// Output: 18
// Explanation: There are 3 almost unique subarrays of size k = 4. These subarrays are [2, 6, 7, 3], [6, 7, 3, 1], and [7, 3, 1, 7]. Among these subarrays, the one with the maximum sum is [2, 6, 7, 3] which has a sum of 18.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= m <= k <= nums.length
// 	1 <= nums[i] <= 109
//

long long maxSum(int* nums, int numsSize, int m, int k) {
    long long max_sum = 0;
    long long current_sum = 0;
    int count_map[20001] = {0};
    int distinct_count = 0;

    for (int i = 0; i < numsSize; i++) {
        current_sum += nums[i];
        count_map[nums[i]]++;
        if (count_map[nums[i]] == 1) {
            distinct_count++;
        }

        if (i >= k) {
            current_sum -= nums[i - k];
            count_map[nums[i - k]]--;
            if (count_map[nums[i - k]] == 0) {
                distinct_count--;
            }
        }

        if (i >= k - 1 && distinct_count >= m) {
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }

    return max_sum;     
}
