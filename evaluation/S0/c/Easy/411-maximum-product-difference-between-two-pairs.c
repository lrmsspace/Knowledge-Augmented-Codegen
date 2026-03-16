// Source: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/   |   Difficulty: Easy
//
// Problem Description:
// The product difference between two pairs (a, b) and (c, d) is defined as (a * b) - (c * d).
//
//
// 	For example, the product difference between (5, 6) and (2, 7) is (5 * 6) - (2 * 7) = 16.
//
//
// Given an integer array nums, choose four distinct indices w, x, y, and z such that the product difference between pairs (nums[w], nums[x]) and (nums[y], nums[z]) is maximized.
//
// Return the maximum such product difference.
//
// Example:
// Input: nums = [5,6,2,7,4]
// Output: 34
// Explanation: We can choose indices 1 and 3 for the first pair (6, 7) and indices 2 and 4 for the second pair (2, 4).
// The product difference is (6 * 7) - (2 * 4) = 34.
//
// Constraints:
// 4 <= nums.length <= 104
// 	1 <= nums[i] <= 104
//

int maxProductDifference(int* nums, int numsSize){


    int max1 = 0, max2 = 0;
    int min1 = 10001, min2 = 10001;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max1) {
            max2 = max1;
            max1 = nums[i];
        } else if (nums[i] > max2) {
            max2 = nums[i];
        }

        if (nums[i] < min1) {
            min2 = min1;
            min1 = nums[i];
        } else if (nums[i] < min2) {
            min2 = nums[i];
        }
    }

    return (max1 * max2) - (min1 * min2);
}
