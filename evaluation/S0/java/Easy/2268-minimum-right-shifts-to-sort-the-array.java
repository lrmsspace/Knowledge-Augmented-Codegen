// Source: https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of length n containing distinct positive integers. Return the minimum number of right shifts required to sort nums and -1 if this is not possible.
//
// A right shift is defined as shifting the element at index i to index (i + 1) % n, for all indices.
//
// Example:
// Input: nums = [3,4,5,1,2]
// Output: 2
// Explanation: 
// After the first right shift, nums = [2,3,4,5,1].
// After the second right shift, nums = [1,2,3,4,5].
// Now nums is sorted; therefore the answer is 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	nums contains distinct integers.
//

class Solution {
    public int minimumRightShifts(List<Integer> nums) {
        int n = nums.size();
        int count = 0;
        int index = -1;

        // Find the index where the array is not sorted
        for (int i = 1; i < n; i++) {
            if (nums.get(i) < nums.get(i - 1)) {
                count++;
                index = i;
            }
            if (count > 1) {
                return -1; // More than one unsorted point means it's not possible
            }
        }

        // If the array is already sorted
        if (count == 0) {
            return 0;
        }

        // Check if the last element is less than or equal to the first element
        if (nums.get(n - 1) > nums.get(0)) {
            return -1; // Not possible to sort with right shifts
        }

        // The number of right shifts needed is the distance from the unsorted point to the end
        return n - index;           
    }
}
