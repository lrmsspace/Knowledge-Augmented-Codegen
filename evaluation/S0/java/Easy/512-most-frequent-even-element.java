// Source: https://leetcode.com/problems/most-frequent-even-element/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the most frequent even element.
//
// If there is a tie, return the smallest one. If there is no such element, return -1.
//
// Example:
// Input: nums = [0,1,2,2,4,4,1]
// Output: 2
// Explanation:
// The even elements are 0, 2, and 4. Of these, 2 and 4 appear the most.
// We return the smallest one, which is 2.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	0 <= nums[i] <= 105
//

class Solution {
    public int mostFrequentEven(int[] nums) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            if (num % 2 == 0) {
                frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
            }
        }

        int mostFrequentEven = -1;
        int highestFrequency = 0;

        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int num = entry.getKey();
            int frequency = entry.getValue();

            if (frequency > highestFrequency || (frequency == highestFrequency && num < mostFrequentEven)) {
                mostFrequentEven = num;
                highestFrequency = frequency;
            }
        }

        return mostFrequentEven;            
    }
}
