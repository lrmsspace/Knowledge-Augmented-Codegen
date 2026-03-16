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

class Solution {
    public int tupleSameProduct(int[] nums) {
        Map<Integer, Integer> productCount = new HashMap<>();
        int n = nums.length;

        // Calculate the product of every pair and count occurrences
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int product = nums[i] * nums[j];
                productCount.put(product, productCount.getOrDefault(product, 0) + 1);
            }
        }

        int result = 0;

        // For each product with count k, add 8 * C(k, 2) to the result
        for (int count : productCount.values()) {
            if (count > 1) {
                result += 8 * (count * (count - 1)) / 2;
            }
        }

        return result;          
    }
}
