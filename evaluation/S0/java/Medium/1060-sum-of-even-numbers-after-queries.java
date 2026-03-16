// Source: https://leetcode.com/problems/sum-of-even-numbers-after-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an array queries where queries[i] = [vali, indexi].
//
// For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even values of nums.
//
// Return an integer array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: nums = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
// Output: [8,6,2,4]
// Explanation: At the beginning, the array is [1,2,3,4].
// After adding 1 to nums[0], the array is [2,2,3,4], and the sum of even values is 2 + 2 + 4 = 8.
// After adding -3 to nums[1], the array is [2,-1,3,4], and the sum of even values is 2 + 4 = 6.
// After adding -4 to nums[0], the array is [-2,-1,3,4], and the sum of even values is -2 + 4 = 2.
// After adding 2 to nums[3], the array is [-2,-1,3,6], and the sum of even values is -2 + 6 = 4.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-104 <= nums[i] <= 104
// 	1 <= queries.length <= 104
// 	-104 <= vali <= 104
// 	0 <= indexi < nums.length
//

class Solution {
    public int[] sumEvenAfterQueries(int[] nums, int[][] queries) {
        int evenSum = 0;
        for (int num : nums) {
            if (num % 2 == 0) {
                evenSum += num;
            }
        }

        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int val = queries[i][0];
            int index = queries[i][1];

            // If the current number is even, subtract it from evenSum
            if (nums[index] % 2 == 0) {
                evenSum -= nums[index];
            }

            // Update the number at the specified index
            nums[index] += val;

            // If the updated number is even, add it to evenSum
            if (nums[index] % 2 == 0) {
                evenSum += nums[index];
            }

            // Store the current even sum in the result array
            result[i] = evenSum;
        }

        return result;          
    }
}
