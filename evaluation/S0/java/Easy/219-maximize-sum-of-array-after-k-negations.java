// Source: https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, modify the array in the following way:
//
//
// 	choose an index i and replace nums[i] with -nums[i].
//
//
// You should apply this process exactly k times. You may choose the same index i multiple times.
//
// Return the largest possible sum of the array after modifying it in this way.
//
// Example:
// Input: nums = [4,2,3], k = 1
// Output: 5
// Explanation: Choose index 1 and nums becomes [4,-2,3].
//
// Constraints:
// 1 <= nums.length <= 104
// 	-100 <= nums[i] <= 100
// 	1 <= k <= 104
//

class Solution {
    public int largestSumAfterKNegations(int[] nums, int k) {
        Arrays.sort(nums);
        int i = 0;
        while (k > 0) {
            if (i < nums.length && nums[i] < 0) {
                nums[i] = -nums[i];
                i++;
            } else {
                if (i == 0 || (i < nums.length && nums[i] < nums[i - 1])) {
                    nums[i - 1] = -nums[i - 1];
                } else {
                    nums[i] = -nums[i];
                }
            }
            k--;
        }
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum;         
    }
}
