// Source: https://leetcode.com/problems/maximum-product-of-three-numbers/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, find three numbers whose product is maximum and return the maximum product.
//
// Example:
// Input: nums = [1,2,3]
// Output: 6
//
// Constraints:
// 3 <= nums.length <= 104
// 	-1000 <= nums[i] <= 1000
//

int maximumProduct(int* nums, int numsSize) {
    int max1 = -1001, max2 = -1001, max3 = -1001;
    int min1 = 1001, min2 = 1001;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        // Update maximums
        if (num > max1) {
            max3 = max2;
            max2 = max1;
            max1 = num;
        } else if (num > max2) {
            max3 = max2;
            max2 = num;
        } else if (num > max3) {
            max3 = num;
        }

        // Update minimums
        if (num < min1) {
            min2 = min1;
            min1 = num;
        } else if (num < min2) {
            min2 = num;
        }
    }

    int product1 = max1 * max2 * max3;
    int product2 = max1 * min1 * min2;

    return product1 > product2 ? product1 : product2;       
}
