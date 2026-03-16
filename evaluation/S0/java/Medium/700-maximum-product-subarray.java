// Source: https://leetcode.com/problems/maximum-product-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find a subarray that has the largest product, and return the product.
//
// The test cases are generated so that the answer will fit in a 32-bit integer.
//
// Example:
// Input: nums = [2,3,-2,4]
// Output: 6
// Explanation: [2,3] has the largest product 6.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-10 <= nums[i] <= 10
// 	The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
//

class Solution {
    public int maxProduct(int[] nums) {
        int maxProduct = nums[0];
        int currMax = nums[0];
        int currMin = nums[0];

        for (int i = 1; i < nums.length; i++) {
            if (nums[i] < 0) {
                int temp = currMax;
                currMax = currMin;
                currMin = temp;
            }

            currMax = Math.max(nums[i], currMax * nums[i]);
            currMin = Math.min(nums[i], currMin * nums[i]);

            maxProduct = Math.max(maxProduct, currMax);
        }

        return maxProduct;          
    }
}
