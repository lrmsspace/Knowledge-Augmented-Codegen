// Source: https://leetcode.com/problems/maximum-strength-of-a-group/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the score of students in an exam. The teacher would like to form one non-empty group of students with maximal strength, where the strength of a group of students of indices i0, i1, i2, ... , ik is defined as nums[i0] * nums[i1] * nums[i2] * ... * nums[ik​].
//
// Return the maximum strength of a group the teacher can create.
//
// Example:
// Input: nums = [3,-1,-5,2,5,-9]
// Output: 1350
// Explanation: One way to form a group of maximal strength is to group the students at indices [0,2,3,4,5]. Their strength is 3 * (-5) * 2 * 5 * (-9) = 1350, which we can show is optimal.
//
// Constraints:
// 1 <= nums.length <= 13
// 	-9 <= nums[i] <= 9
//

class Solution {
    public long maxStrength(int[] nums) {
        long maxStrength = Long.MIN_VALUE;
        int n = nums.length;

        // There are 2^n - 1 non-empty subsets
        for (int mask = 1; mask < (1 << n); mask++) {
            long product = 1;
            for (int i = 0; i < n; i++) {
                // Check if the i-th element is included in the current subset
                if ((mask & (1 << i)) != 0) {
                    product *= nums[i];
                }
            }
            maxStrength = Math.max(maxStrength, product);
        }

        return maxStrength;         
    }
}
