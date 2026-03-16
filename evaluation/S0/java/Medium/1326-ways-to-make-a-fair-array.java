// Source: https://leetcode.com/problems/ways-to-make-a-fair-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.
//
// For example, if nums = [6,1,7,4,1]:
//
//
// 	Choosing to remove index 1 results in nums = [6,7,4,1].
// 	Choosing to remove index 2 results in nums = [6,1,4,1].
// 	Choosing to remove index 4 results in nums = [6,1,7,4].
//
//
// An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.
//
// Return the number of indices that you could choose such that after the removal, nums is fair.
//
// Example:
// Input: nums = [2,1,6,4]
// Output: 1
// Explanation:
// Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
// Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
// Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
// Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
// There is 1 index that you can remove to make nums fair.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//

class Solution {
    public int waysToMakeFair(int[] nums) {
        int n = nums.length;
        int[] oddPrefix = new int[n + 1];
        int[] evenPrefix = new int[n + 1];

        for (int i = 0; i < n; i++) {
            oddPrefix[i + 1] = oddPrefix[i];
            evenPrefix[i + 1] = evenPrefix[i];
            if (i % 2 == 0) {
                evenPrefix[i + 1] += nums[i];
            } else {
                oddPrefix[i + 1] += nums[i];
            }
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            int evenSum = evenPrefix[i] + (oddPrefix[n] - oddPrefix[i + 1]);
            int oddSum = oddPrefix[i] + (evenPrefix[n] - evenPrefix[i + 1]);
            if (evenSum == oddSum) {
                count++;
            }
        }

        return count;           
    }
}
