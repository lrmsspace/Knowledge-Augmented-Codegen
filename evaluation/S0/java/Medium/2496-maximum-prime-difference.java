// Source: https://leetcode.com/problems/maximum-prime-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// Return an integer that is the maximum distance between the indices of two (not necessarily different) prime numbers in nums.
//
// Example:
// Input: nums = [4,2,9,5,3]
//
// Output: 3
//
// Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is |4 - 1| = 3.
//
// Constraints:
// 1 <= nums.length <= 3 * 105
// 	1 <= nums[i] <= 100
// 	The input is generated such that the number of prime numbers in the nums is at least one.
//

class Solution {
    public int maximumPrimeDifference(int[] nums) {
        boolean[] isPrime = new boolean[101];
        isPrime[2] = true;
        isPrime[3] = true;
        isPrime[5] = true;
        isPrime[7] = true;
        isPrime[11] = true;
        isPrime[13] = true;
        isPrime[17] = true;
        isPrime[19] = true;
        isPrime[23] = true;
        isPrime[29] = true;
        isPrime[31] = true;
        isPrime[37] = true;
        isPrime[41] = true;
        isPrime[43] = true;
        isPrime[47] = true;
        isPrime[53] = true;
        isPrime[59] = true;
        isPrime[61] = true;
        isPrime[67] = true;
        isPrime[71] = true;
        isPrime[73] = true;
        isPrime[79] = true;
        isPrime[83] = true;
        isPrime[89] = true;
        isPrime[97] = true;

        int firstIndex = -1;
        int lastIndex = -1;

        for (int i = 0; i < nums.length; i++) {
            if (isPrime[nums[i]]) {
                if (firstIndex == -1) {
                    firstIndex = i;
                }
                lastIndex = i;
            }
        }

        return lastIndex - firstIndex;          
    }
}
