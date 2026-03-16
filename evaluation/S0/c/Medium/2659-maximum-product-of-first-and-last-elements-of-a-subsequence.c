// Source: https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer m.
//
// Return the maximum product of the first and last elements of any subsequence of nums of size m.
//
// Example:
// Input: nums = [-1,-9,2,3,-2,-3,1], m = 1
//
// Output: 81
//
// Explanation:
//
// The subsequence [-9] has the largest product of the first and last elements: -9 * -9 = 81. Therefore, the answer is 81.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-105 <= nums[i] <= 105
// 	1 <= m <= nums.length
//

long long maximumProduct(int* nums, int numsSize, int m) {
    long long max_product = -1e18; // Initialize to a very small number

    for (int i = 0; i <= numsSize - m; i++) {
        long long product = (long long)nums[i] * (long long)nums[i + m - 1];
        if (product > max_product) {
            max_product = product;
        }
    }

    return max_product;     
}
