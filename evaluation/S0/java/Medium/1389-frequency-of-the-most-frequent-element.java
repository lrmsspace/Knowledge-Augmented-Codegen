// Source: https://leetcode.com/problems/frequency-of-the-most-frequent-element/   |   Difficulty: Medium
//
// Problem Description:
// The frequency of an element is the number of times it occurs in an array.
//
// You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and increment the element at that index by 1.
//
// Return the maximum possible frequency of an element after performing at most k operations.
//
// Example:
// Input: nums = [1,2,4], k = 5
// Output: 3
// Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
// 4 has a frequency of 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= 105
//

class Solution {
    public int maxFrequency(int[] nums, int k) {
        Arrays.sort(nums);
        int left = 0;
        int total = 0;
        int result = 1;

        for (int right = 1; right < nums.length; right++) {
            total += (nums[right] - nums[right - 1]) * (right - left);

            while (total > k) {
                total -= nums[right] - nums[left];
                left++;
            }

            result = Math.max(result, right - left + 1);
        }

        return result;          
    }
}
