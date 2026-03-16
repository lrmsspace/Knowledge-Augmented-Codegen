// Source: https://leetcode.com/problems/132-pattern/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
//
// Return true if there is a 132 pattern in nums, otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: false
// Explanation: There is no 132 pattern in the sequence.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 2 * 105
// 	-109 <= nums[i] <= 109
//

class Solution {
    public boolean find132pattern(int[] nums) {
        int n = nums.length;
        if (n < 3) return false;

        int[] minArray = new int[n];
        minArray[0] = nums[0];
        for (int i = 1; i < n; i++) {
            minArray[i] = Math.min(minArray[i - 1], nums[i]);
        }

        Deque<Integer> stack = new ArrayDeque<>();
        for (int j = n - 1; j >= 0; j--) {
            while (!stack.isEmpty() && stack.peek() <= minArray[j]) {
                stack.pop();
            }
            if (!stack.isEmpty() && stack.peek() < nums[j]) {
                return true;
            }
            stack.push(nums[j]);
        }

        return false;           
    }
}
