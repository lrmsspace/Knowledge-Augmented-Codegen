// Source: https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums.
//
// You need to select a subset of nums which satisfies the following condition:
//
//
// 	You can place the selected elements in a 0-indexed array such that it follows the pattern: [x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] (Note that k can be be any non-negative power of 2). For example, [2, 4, 16, 4, 2] and [3, 9, 3] follow the pattern while [2, 4, 8, 4, 2] does not.
//
//
// Return the maximum number of elements in a subset that satisfies these conditions.
//
// Example:
// Input: nums = [5,4,1,2,2]
// Output: 3
// Explanation: We can select the subset {4,2,2}, which can be placed in the array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer is 3.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int maximumLength(int[] nums) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        int maxLength = 0;

        // Count the frequency of each number in the array
        for (int num : nums) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        // Iterate through each unique number in the frequency map
        for (int num : freqMap.keySet()) {
            int currentNum = num;
            int currentLength = 0;

            // Try to build the subset starting from the current number
            while (freqMap.containsKey(currentNum) && freqMap.get(currentNum) > 0) {
                currentLength++;
                freqMap.put(currentNum, freqMap.get(currentNum) - 1);
                currentNum *= 2; // Move to the next number in the pattern
            }

            // Update the maximum length found so far
            maxLength = Math.max(maxLength, currentLength);
        }

        return maxLength;           
    }
}
