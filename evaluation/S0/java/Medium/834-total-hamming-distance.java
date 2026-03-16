// Source: https://leetcode.com/problems/total-hamming-distance/   |   Difficulty: Medium
//
// Problem Description:
// The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
//
// Given an integer array nums, return the sum of Hamming distances between all the pairs of the integers in nums.
//
// Example:
// Input: nums = [4,14,2]
// Output: 6
// Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
// showing the four bits relevant in this case).
// The answer will be:
// HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
//
// Constraints:
// 1 <= nums.length <= 104
// 	0 <= nums[i] <= 109
// 	The answer for the given input will fit in a 32-bit integer.
//

class Solution {
    public int totalHammingDistance(int[] nums) {
        int totalDistance = 0;
        int n = nums.length;

        // Iterate through each bit position (0 to 31 for 32-bit integers)
        for (int bitPosition = 0; bitPosition < 32; bitPosition++) {
            int countOnes = 0;

            // Count how many numbers have the current bit set
            for (int num : nums) {
                if ((num & (1 << bitPosition)) != 0) {
                    countOnes++;
                }
            }

            // The number of numbers with the current bit not set
            int countZeros = n - countOnes;

            // Each pair of one '1' and one '0' contributes to the Hamming distance
            totalDistance += countOnes * countZeros;
        }

        return totalDistance;           
    }
}
