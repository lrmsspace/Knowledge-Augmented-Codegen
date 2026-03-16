// Source: https://leetcode.com/problems/product-of-array-except-self/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
//
// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
//
// You must write an algorithm that runs in O(n) time and without using the division operation.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: [24,12,8,6]
//
// Constraints:
// 2 <= nums.length <= 105
// 	-30 <= nums[i] <= 30
// 	The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
//
//
//  
// Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
//

class Solution {
    public int[] productExceptSelf(int[] nums) {
        int n = nums.length;
        int[] answer = new int[n];

        // Calculate left products
        answer[0] = 1;
        for (int i = 1; i < n; i++) {
            answer[i] = answer[i - 1] * nums[i - 1];
        }

        // Calculate right products and combine with left products
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            answer[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return answer;          
    }
}
