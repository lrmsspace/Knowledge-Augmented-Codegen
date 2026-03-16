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
public:
    int totalHammingDistance(vector<int>& nums) {
        int totalDistance = 0;
        int n = nums.size();

        for (int bit = 0; bit < 32; ++bit) {
            int countOnes = 0;
            for (int num : nums) {
                if (num & (1 << bit)) {
                    countOnes++;
                }
            }
            int countZeros = n - countOnes;
            totalDistance += countOnes * countZeros;
        }

        return totalDistance;           
    }
};
