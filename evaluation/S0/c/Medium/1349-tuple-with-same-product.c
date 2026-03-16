// Source: https://leetcode.com/problems/tuple-with-same-product/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
//
// Example:
// Input: nums = [2,3,4,6]
// Output: 8
// Explanation: There are 8 valid tuples:
// (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
// (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 104
// 	All elements in nums are distinct.
//

int tupleSameProduct(int* nums, int numsSize) {
    int productCount[100000000] = {0};
    int result = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            int product = nums[i] * nums[j];
            productCount[product]++;
        }
    }

    for (int i = 0; i < 100000000; i++) {
        if (productCount[i] > 1) {
            int count = productCount[i];
            result += count * (count - 1) * 4;
        }
    }

    return result;      
}
