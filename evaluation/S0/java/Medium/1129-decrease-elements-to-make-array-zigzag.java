// Source: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
//
// An array A is a zigzag array if either:
//
//
//  Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
//  OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
//
//
// Return the minimum number of moves to transform the given array nums into a zigzag array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation: We can decrease 2 to 0 or 3 to 1.
//
// Constraints:
// 1 <= nums.length <= 1000
//  1 <= nums[i] <= 1000
//

class Solution {
    public int movesToMakeZigzag(int[] nums) {
        int n = nums.length;
        int evenMoves = 0;
        int oddMoves = 0;

        for (int i = 0; i < n; i++) {
            int left = (i > 0) ? nums[i - 1] : Integer.MAX_VALUE;
            int right = (i < n - 1) ? nums[i + 1] : Integer.MAX_VALUE;
            int decreaseTo = Math.min(left, right) - 1;

            if (i % 2 == 0) {
                if (nums[i] >= decreaseTo) {
                    evenMoves += nums[i] - decreaseTo;
                }
            } else {
                if (nums[i] >= decreaseTo) {
                    oddMoves += nums[i] - decreaseTo;
                }
            }
        }

        return Math.min(evenMoves, oddMoves);           
    }
}
