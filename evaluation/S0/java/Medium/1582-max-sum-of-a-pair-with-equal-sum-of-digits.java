// Source: https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].
//
// Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions. If no such pair of indices exists, return -1.
//
// Example:
// Input: nums = [18,43,36,13,7]
// Output: 54
// Explanation: The pairs (i, j) that satisfy the conditions are:
// - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
// - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
// So the maximum sum that we can obtain is 54.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int maximumSum(int[] nums) {
        Map<Integer, Integer> map = new HashMap<>();
        int maxSum = -1;

        for (int num : nums) {
            int digitSum = getDigitSum(num);

            if (map.containsKey(digitSum)) {
                int currentMax = map.get(digitSum);
                maxSum = Math.max(maxSum, currentMax + num);
                map.put(digitSum, Math.max(currentMax, num));
            } else {
                map.put(digitSum, num);
            }
        }

        return maxSum;          
    }
}
