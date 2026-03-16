// Source: https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of subarrays of nums where the bitwise AND of the elements of the subarray equals k.
//
// Example:
// Input: nums = [1,1,1], k = 1
//
// Output: 6
//
// Explanation:
//
// All subarrays contain only 1's.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i], k <= 109
//

long long countSubarrays(int* nums, int numsSize, int k) {
    long long result = 0;
    int count = 0; /* count of consecutive elements where (num & k) == k */
    for (int i = 0; i < numsSize; ++i) {
        if ((nums[i] & k) == k) {
            count++;
        } else {
            count = 0;
        }
        if ((nums[i] & k) == k && (nums[i] | k) == k) {
            result += count;
        }
    }
    return result;      
}
