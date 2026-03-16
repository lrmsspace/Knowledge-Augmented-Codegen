// Source: https://leetcode.com/problems/count-the-number-of-fair-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed integer array nums of size n and two integers lower and upper, return the number of fair pairs.
//
// A pair (i, j) is fair if:
//
//
// 	0 <= i < j < n, and
// 	lower <= nums[i] + nums[j] <= upper
//
// Example:
// Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
// Output: 6
// Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and (1,5).
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums.length == n
// 	-109 <= nums[i] <= 109
// 	-109 <= lower <= upper <= 109
//

class Solution {
    public long countFairPairs(int[] nums, int lower, int upper) {
        Arrays.sort(nums);
        return countPairs(nums, upper) - countPairs(nums, lower - 1);           
    }
}
