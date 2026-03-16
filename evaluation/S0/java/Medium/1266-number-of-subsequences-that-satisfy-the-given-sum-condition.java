// Source: https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and an integer target.
//
// Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [3,5,6,7], target = 9
// Output: 4
// Explanation: There are 4 subsequences that satisfy the condition.
// [3] -> Min value + max value <= target (3 + 3 <= 9)
// [3,5] -> (3 + 5 <= 9)
// [3,5,6] -> (3 + 6 <= 9)
// [3,6] -> (3 + 6 <= 9)
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= target <= 106
//

class Solution {
    public int numSubseq(int[] nums, int target) {
        Arrays.sort(nums);
        int mod = 1_000_000_007;
        int left = 0, right = nums.length - 1;
        int[] pow = new int[nums.length];
        pow[0] = 1;
        for (int i = 1; i < nums.length; i++) {
            pow[i] = (pow[i - 1] * 2) % mod;
        }
        int result = 0;
        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                result = (result + pow[right - left]) % mod;
                left++;
            } else {
                right--;
            }
        }
        return result;          
    }
}
