// Source: https://leetcode.com/problems/delete-and-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You want to maximize the number of points you get by performing the following operation any number of times:
//
//
// 	Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
//
//
// Return the maximum number of points you can earn by applying the above operation some number of times.
//
// Example:
// Input: nums = [3,4,2]
// Output: 6
// Explanation: You can perform the following operations:
// - Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
// - Delete 2 to earn 2 points. nums = [].
// You earn a total of 6 points.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 104
//

class Solution {
    public int deleteAndEarn(int[] nums) {
        int maxVal = 0;
        for (int num : nums) {
            maxVal = Math.max(maxVal, num);
        }

        int[] points = new int[maxVal + 1];
        for (int num : nums) {
            points[num] += num;
        }

        int take = 0;
        int skip = 0;

        for (int point : points) {
            int takei = skip + point;
            int skipi = Math.max(skip, take);

            take = takei;
            skip = skipi;
        }

        return Math.max(take, skip);            
    }
}
