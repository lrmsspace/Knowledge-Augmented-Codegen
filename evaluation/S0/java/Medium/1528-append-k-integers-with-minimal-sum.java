// Source: https://leetcode.com/problems/append-k-integers-with-minimal-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Append k unique positive integers that do not appear in nums to nums such that the resulting total sum is minimum.
//
// Return the sum of the k integers appended to nums.
//
// Example:
// Input: nums = [1,4,25,10,25], k = 2
// Output: 5
// Explanation: The two unique positive integers that do not appear in nums which we append are 2 and 3.
// The resulting sum of nums is 1 + 4 + 25 + 10 + 25 + 2 + 3 = 70, which is the minimum.
// The sum of the two integers appended is 2 + 3 = 5, so we return 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 108
//

class Solution {
    public long minimalKSum(int[] nums, int k) {
        Arrays.sort(nums);
        long result = 0;
        long nextNumToAdd = 1;
        int n = nums.length;

        for (int i = 0; i < n && k > 0; i++) {
            if (nums[i] < nextNumToAdd) {
                continue; // Skip duplicates and numbers less than nextNumToAdd
            }

            // Calculate how many numbers we can add before nums[i]
            long count = nums[i] - nextNumToAdd;
            if (count >= k) {
                // We can add all remaining k numbers before nums[i]
                result += sumOfFirstN(nextNumToAdd, k);
                return result;
            } else {
                // Add all numbers from nextNumToAdd to nums[i] - 1
                result += sumOfFirstN(nextNumToAdd, count);
                k -= count;
                nextNumToAdd = (long) nums[i] + 1; // Update nextNumToAdd
            }
        }

        // If there are still k numbers to add after processing all nums
        if (k > 0) {
            result += sumOfFirstN(nextNumToAdd, k);
        }

        return result;          
    }
}
