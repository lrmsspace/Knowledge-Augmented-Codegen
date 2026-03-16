// Source: https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/   |   Difficulty: Medium
//
// Problem Description:
// A swap is defined as taking two distinct positions in an array and swapping the values in them.
//
// A circular array is defined as an array where we consider the first element and the last element to be adjacent.
//
// Given a binary circular array nums, return the minimum number of swaps required to group all 1's present in the array together at any location.
//
// Example:
// Input: nums = [0,1,0,1,1,0,0]
// Output: 1
// Explanation: Here are a few of the ways to group all the 1's together:
// [0,0,1,1,1,0,0] using 1 swap.
// [0,1,1,1,0,0,0] using 1 swap.
// [1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
// There is no way to group all 1's together with 0 swaps.
// Thus, the minimum number of swaps required is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

class Solution {
    public int minSwaps(int[] nums) {
        int totalOnes = 0;
        for (int num : nums) {
            if (num == 1) {
                totalOnes++;
            }
        }

        if (totalOnes == 0 || totalOnes == nums.length) {
            return 0;
        }

        int currentOnes = 0;
        for (int i = 0; i < totalOnes; i++) {
            if (nums[i] == 1) {
                currentOnes++;
            }
        }

        int maxOnesInWindow = currentOnes;
        int n = nums.length;

        for (int i = totalOnes; i < n + totalOnes; i++) {
            if (nums[i % n] == 1) {
                currentOnes++;
            }
            if (nums[(i - totalOnes) % n] == 1) {
                currentOnes--;
            }
            maxOnesInWindow = Math.max(maxOnesInWindow, currentOnes);
        }

        return totalOnes - maxOnesInWindow;         
    }
}
