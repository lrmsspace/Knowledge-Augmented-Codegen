// Source: https://leetcode.com/problems/maximum-equal-frequency/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers, return the longest possible length of an array prefix of nums, such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.
//
// If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).
//
// Example:
// Input: nums = [2,2,1,1,5,3,3,5]
// Output: 7
// Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4] = 5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public int maxEqualFreq(int[] nums) {
        int n = nums.length;
        int[] count = new int[100001];
        int[] freq = new int[100001];
        int res = 0;

        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (count[num] > 0) {
                freq[count[num]]--;
            }
            count[num]++;
            freq[count[num]]++;

            boolean condition1 = freq[1] == i + 1; // All numbers appear once
            boolean condition2 = freq[i + 1] == 1; // One number appears i+1 times, others are zero
            boolean condition3 = freq[i] == 1 && freq[i + 1] * (i + 1) + freq[i] * i == i + 1; // One number appears once more than others
            boolean condition4 = freq[1] == 1 && freq[i] * i + freq[1] == i + 1; // One number appears once, others appear i times

            if (condition1 || condition2 || condition3 || condition4) {
                res = i + 1;
            }
        }

        return res;                 
    }
}
