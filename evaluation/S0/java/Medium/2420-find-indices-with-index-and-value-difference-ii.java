// Source: https://leetcode.com/problems/find-indices-with-index-and-value-difference-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums having length n, an integer indexDifference, and an integer valueDifference.
//
// Your task is to find two indices i and j, both in the range [0, n - 1], that satisfy the following conditions:
//
//
// 	abs(i - j) >= indexDifference, and
// 	abs(nums[i] - nums[j]) >= valueDifference
//
//
// Return an integer array answer, where answer = [i, j] if there are two such indices, and answer = [-1, -1] otherwise. If there are multiple choices for the two indices, return any of them.
//
// Note: i and j may be equal.
//
// Example:
// Input: nums = [5,1,4,1], indexDifference = 2, valueDifference = 4
// Output: [0,3]
// Explanation: In this example, i = 0 and j = 3 can be selected.
// abs(0 - 3) >= 2 and abs(nums[0] - nums[3]) >= 4.
// Hence, a valid answer is [0,3].
// [3,0] is also a valid answer.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= indexDifference <= 105
// 	0 <= valueDifference <= 109
//

class Solution {
    public int[] findIndices(int[] nums, int indexDifference, int valueDifference) {
        TreeSet<Integer> set = new TreeSet<>();
        for (int i = 0; i < nums.length; i++) {
            if (i > indexDifference) {
                set.add(nums[i - indexDifference - 1]);
            }
            Integer lower = set.floor(nums[i] - valueDifference);
            if (lower != null && Math.abs(lower - nums[i]) >= valueDifference) {
                return new int[]{i, indexOf(nums, lower, i - indexDifference - 1)};
            }
            Integer higher = set.ceiling(nums[i] + valueDifference);
            if (higher != null && Math.abs(higher - nums[i]) >= valueDifference) {
                return new int[]{i, indexOf(nums, higher, i - indexDifference - 1)};
            }
        }
        return new int[]{-1, -1};           
    }
}
