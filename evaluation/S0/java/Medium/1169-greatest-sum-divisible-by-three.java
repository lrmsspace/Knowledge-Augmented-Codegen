// Source: https://leetcode.com/problems/greatest-sum-divisible-by-three/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.
//
// Example:
// Input: nums = [3,6,5,1,8]
// Output: 18
// Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
//
// Constraints:
// 1 <= nums.length <= 4 * 104
// 	1 <= nums[i] <= 104
//

class Solution {
    public int maxSumDivThree(int[] nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        int remainder = sum % 3;
        if (remainder == 0) {
            return sum;
        }

        int min1 = Integer.MAX_VALUE; // Smallest number with remainder 1
        int min2 = Integer.MAX_VALUE; // Second smallest number with remainder 1
        int min3 = Integer.MAX_VALUE; // Smallest number with remainder 2
        int min4 = Integer.MAX_VALUE; // Second smallest number with remainder 2

        for (int num : nums) {
            if (num % 3 == 1) {
                if (num < min1) {
                    min2 = min1;
                    min1 = num;
                } else if (num < min2) {
                    min2 = num;
                }
            } else if (num % 3 == 2) {
                if (num < min3) {
                    min4 = min3;
                    min3 = num;
                } else if (num < min4) {
                    min4 = num;
                }
            }
        }

        if (remainder == 1) {
            int option1 = (min1 != Integer.MAX_VALUE) ? sum - min1 : 0;
            int option2 = (min3 != Integer.MAX_VALUE && min4 != Integer.MAX_VALUE) ? sum - min3 - min4 : 0;
            return Math.max(option1, option2);
        } else { // remainder == 2
            int option1 = (min3 != Integer.MAX_VALUE) ? sum - min3 : 0;
            int option2 = (min1 != Integer.MAX_VALUE && min2 != Integer.MAX_VALUE) ? sum - min1 - min2 : 0;
            return Math.max(option1, option2);
        }           
    }
}
