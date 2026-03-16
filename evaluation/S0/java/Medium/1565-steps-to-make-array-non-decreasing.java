// Source: https://leetcode.com/problems/steps-to-make-array-non-decreasing/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. In one step, remove all elements nums[i] where nums[i - 1] > nums[i] for all 0 < i < nums.length.
//
// Return the number of steps performed until nums becomes a non-decreasing array.
//
// Example:
// Input: nums = [5,3,4,4,7,3,6,11,8,5,11]
// Output: 3
// Explanation: The following are the steps performed:
// - Step 1: [5,3,4,4,7,3,6,11,8,5,11] becomes [5,4,4,7,6,11,11]
// - Step 2: [5,4,4,7,6,11,11] becomes [5,4,7,11,11]
// - Step 3: [5,4,7,11,11] becomes [5,7,11,11]
// [5,7,11,11] is a non-decreasing array. Therefore, we return 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int totalSteps(int[] nums) {
        int n = nums.length;
        int[] steps = new int[n];
        Deque<Integer> stack = new ArrayDeque<>();
        int maxSteps = 0;

        for (int i = n - 1; i >= 0; i--) {
            int currentSteps = 0;

            while (!stack.isEmpty() && nums[i] > nums[stack.peek()]) {
                currentSteps = Math.max(currentSteps + 1, steps[stack.pop()]);
            }

            steps[i] = currentSteps;
            maxSteps = Math.max(maxSteps, currentSteps);
            stack.push(i);
        }

        return maxSteps;            
    }
}
