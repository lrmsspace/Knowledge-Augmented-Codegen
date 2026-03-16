// Source: https://leetcode.com/problems/count-elements-with-maximum-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Return the total frequencies of elements in nums such that those elements all have the maximum frequency.
//
// The frequency of an element is the number of occurrences of that element in the array.
//
// Example:
// Input: nums = [1,2,2,3,1,4]
// Output: 4
// Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
// So the number of elements in the array with maximum frequency is 4.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

class Solution {
    public int maxFrequencyElements(int[] nums) {
        int[] frequency = new int[101];
        int maxFreq = 0;
        int count = 0;

        for (int num : nums) {
            frequency[num]++;
            if (frequency[num] > maxFreq) {
                maxFreq = frequency[num];
            }
        }

        for (int freq : frequency) {
            if (freq == maxFreq) {
                count += freq;
            }
        }

        return count;           
    }
}
