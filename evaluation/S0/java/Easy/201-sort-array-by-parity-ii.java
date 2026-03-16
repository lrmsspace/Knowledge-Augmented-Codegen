// Source: https://leetcode.com/problems/sort-array-by-parity-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers nums, half of the integers in nums are odd, and the other half are even.
//
// Sort the array so that whenever nums[i] is odd, i is odd, and whenever nums[i] is even, i is even.
//
// Return any answer array that satisfies this condition.
//
// Example:
// Input: nums = [4,2,5,7]
// Output: [4,5,2,7]
// Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
//
// Constraints:
// 2 <= nums.length <= 2 * 104
// 	nums.length is even.
// 	Half of the integers in nums are even.
// 	0 <= nums[i] <= 1000
//
//
//  
// Follow Up: Could you solve it in-place?
//

class Solution {
    public int[] sortArrayByParityII(int[] nums) {
        int evenIndex = 0;
        int oddIndex = 1;
        int n = nums.length;

        while (evenIndex < n && oddIndex < n) {
            if (nums[evenIndex] % 2 == 0) {
                evenIndex += 2;
            } else if (nums[oddIndex] % 2 == 1) {
                oddIndex += 2;
            } else {
                // Swap the elements at evenIndex and oddIndex
                int temp = nums[evenIndex];
                nums[evenIndex] = nums[oddIndex];
                nums[oddIndex] = temp;

                evenIndex += 2;
                oddIndex += 2;
            }
        }

        return nums;            
    }
}
