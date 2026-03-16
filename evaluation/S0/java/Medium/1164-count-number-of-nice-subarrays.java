// Source: https://leetcode.com/problems/count-number-of-nice-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.
//
// Return the number of nice sub-arrays.
//
// Example:
// Input: nums = [1,1,2,1,1], k = 3
// Output: 2
// Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
//
// Constraints:
// 1 <= nums.length <= 50000
// 	1 <= nums[i] <= 10^5
// 	1 <= k <= nums.length
//

class Solution {
    public int numberOfSubarrays(int[] nums, int k) {
        int count = 0;
        int left = 0;
        int right = 0;
        int oddCount = 0;
        int n = nums.length;

        while (right < n) {
            // Expand the window by moving the right pointer
            if (nums[right] % 2 == 1) {
                oddCount++;
            }
            right++;

            // When we have k odd numbers, calculate the number of nice subarrays
            if (oddCount == k) {
                int leftEvenCount = 0;
                int rightEvenCount = 0;

                // Count even numbers on the left side
                while (left < n && nums[left] % 2 == 0) {
                    leftEvenCount++;
                    left++;
                }

                // Count even numbers on the right side
                while (right < n && nums[right] % 2 == 0) {
                    rightEvenCount++;
                    right++;
                }

                // The number of nice subarrays is the product of the counts of even numbers on both sides
                count += (leftEvenCount + 1) * (rightEvenCount + 1);

                // Move left pointer to the next odd number to continue searching for new subarrays
                left++;
                oddCount--;
            }
        }

        return count;           
    }
}
