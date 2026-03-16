// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct integers.
//
// In one operation, you can swap any two adjacent elements in the array.
//
// An arrangement of the array is considered valid if the parity of adjacent elements alternates, meaning every pair of neighboring elements consists of one even and one odd number.
//
// Return the minimum number of adjacent swaps required to transform nums into any valid arrangement.
//
// If it is impossible to rearrange nums such that no two adjacent elements have the same parity, return -1.
//
// Example:
// Input: nums = [2,4,6,5,7]
//
// Output: 3
//
// Explanation:
//
// Swapping 5 and 6, the array becomes [2,4,5,6,7]
//
// Swapping 5 and 4, the array becomes [2,5,4,6,7]
//
// Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid arrangement. Thus, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements in nums are distinct.
//

class Solution {
    public int minSwaps(int[] nums) {
        int n = nums.length;
        int evenCount = 0;
        int oddCount = 0;

        for (int num : nums) {
            if (num % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }

        if (Math.abs(evenCount - oddCount) > 1) {
            return -1;
        }

        int swapsStartingWithEven = calculateSwaps(nums, true);
        int swapsStartingWithOdd = calculateSwaps(nums, false);

        if (evenCount > oddCount) {
            return swapsStartingWithEven;
        } else if (oddCount > evenCount) {
            return swapsStartingWithOdd;
        } else {
            return Math.min(swapsStartingWithEven, swapsStartingWithOdd);
        }           
    }
}
