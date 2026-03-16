// Source: https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// You are allowed to delete any number of elements from nums without making it empty. After performing the deletions, select a subarray of nums such that:
//
//
// 	All elements in the subarray are unique.
// 	The sum of the elements in the subarray is maximized.
//
//
// Return the maximum sum of such a subarray.
//
// Example:
// Input: nums = [1,2,3,4,5]
//
// Output: 15
//
// Explanation:
//
// Select the entire array without deleting any element to obtain the maximum sum.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

int maxSum(int* nums, int numsSize) {
    int max_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        int current_sum = 0;
        int seen[201] = {0}; // To track seen numbers, offset by 100 to handle negative numbers
        for (int j = i; j < numsSize; j++) {
            int num = nums[j] + 100; // Offset to handle negative numbers
            if (seen[num]) {
                break; // Duplicate found, break the inner loop
            }
            seen[num] = 1; // Mark this number as seen
            current_sum += nums[j];
            if (current_sum > max_sum) {
                max_sum = current_sum; // Update max_sum if current_sum is greater
            }
        }
    }
    return max_sum;     
}
