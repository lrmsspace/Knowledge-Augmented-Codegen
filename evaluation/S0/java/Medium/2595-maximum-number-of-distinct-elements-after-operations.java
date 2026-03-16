// Source: https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// You are allowed to perform the following operation on each element of the array at most once:
//
//
// 	Add an integer in the range [-k, k] to the element.
//
//
// Return the maximum possible number of distinct elements in nums after performing the operations.
//
// Example:
// Input: nums = [1,2,2,3,3,4], k = 2
//
// Output: 6
//
// Explanation:
//
// nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the first four elements.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//

class Solution {
    public int maxDistinctElements(int[] nums, int k) {
        Set<Integer> distinct = new HashSet<>();
        for (int num : nums) {
            if (k > 0) {
                for (int delta = -k; delta <= k; delta++) {
                    if (!distinct.contains(num + delta)) {
                        distinct.add(num + delta);
                        break;
                    }
                }
            } else {
                distinct.add(num);
            }
        }
        return distinct.size();         
    }
}
