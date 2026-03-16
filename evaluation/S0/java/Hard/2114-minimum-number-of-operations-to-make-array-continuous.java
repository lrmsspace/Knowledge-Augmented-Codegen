// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. In one operation, you can replace any element in nums with any integer.
//
// nums is considered continuous if both of the following conditions are fulfilled:
//
//
// 	All elements in nums are unique.
// 	The difference between the maximum element and the minimum element in nums equals nums.length - 1.
//
//
// For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.
//
// Return the minimum number of operations to make nums continuous.
//
// Example:
// Input: nums = [4,2,5,3]
// Output: 0
// Explanation: nums is already continuous.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }
        Integer[] uniqueNums = set.toArray(new Integer[0]);
        Arrays.sort(uniqueNums);

        int left = 0;
        int maxWindowSize = 0;
        for (int right = 0; right < uniqueNums.length; right++) {
            while (uniqueNums[right] - uniqueNums[left] >= n) {
                left++;
            }
            maxWindowSize = Math.max(maxWindowSize, right - left + 1);
        }

        return n - maxWindowSize;           
    }
}
