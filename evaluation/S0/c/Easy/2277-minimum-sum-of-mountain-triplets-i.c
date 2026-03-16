// Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of integers.
//
// A triplet of indices (i, j, k) is a mountain if:
//
//
// 	i < j < k
// 	nums[i] < nums[j] and nums[k] < nums[j]
//
//
// Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
//
// Example:
// Input: nums = [8,6,1,5,3]
// Output: 9
// Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
// - 2 < 3 < 4
// - nums[2] < nums[3] and nums[4] < nums[3]
// And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
//
// Constraints:
// 3 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

int minimumSum(int* nums, int numsSize) {
    int min_sum = -1;

    for (int j = 1; j < numsSize - 1; ++j) {
        int left_min = -1;
        for (int i = 0; i < j; ++i) {
            if (nums[i] < nums[j]) {
                if (left_min == -1 || nums[i] < left_min) {
                    left_min = nums[i];
                }
            }
        }

        int right_min = -1;
        for (int k = j + 1; k < numsSize; ++k) {
            if (nums[k] < nums[j]) {
                if (right_min == -1 || nums[k] < right_min) {
                    right_min = nums[k];
                }
            }
        }

        if (left_min != -1 && right_min != -1) {
            int current_sum = left_min + nums[j] + right_min;
            if (min_sum == -1 || current_sum < min_sum) {
                min_sum = current_sum;
            }
        }
    }

    return min_sum;     
}
