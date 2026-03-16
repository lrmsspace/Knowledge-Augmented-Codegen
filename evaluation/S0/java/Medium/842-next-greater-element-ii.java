// Source: https://leetcode.com/problems/next-greater-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.
//
// The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.
//
// Example:
// Input: nums = [1,2,1]
// Output: [2,-1,2]
// Explanation: The first 1's next greater number is 2; 
// The number 2 can't find next greater number. 
// The second 1's next greater number needs to search circularly, which is also 2.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-109 <= nums[i] <= 109
//

class Solution {
    public int[] nextGreaterElements(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < 2 * n; i++) {
            int currentIndex = i % n;
            while (!stack.isEmpty() && nums[stack.peek()] < nums[currentIndex]) {
                int index = stack.pop();
                result[index] = nums[currentIndex];
            }
            if (i < n) {
                stack.push(currentIndex);
            }
        }

        return result;          
    }
}
