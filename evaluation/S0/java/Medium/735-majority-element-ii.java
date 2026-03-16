// Source: https://leetcode.com/problems/majority-element-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
//
// Example:
// Input: nums = [3,2,3]
// Output: [3]
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow up: Could you solve the problem in linear time and in O(1) space?
//

class Solution {
    public List<Integer> majorityElement(int[] nums) {
        List<Integer> result = new ArrayList<>();
        int count1 = 0, count2 = 0;
        Integer candidate1 = null, candidate2 = null;

        for (int num : nums) {
            if (candidate1 != null && num == candidate1.intValue()) {
                count1++;
            } else if (candidate2 != null && num == candidate2.intValue()) {
                count2++;
            } else if (count1 == 0) {
                candidate1 = num;
                count1 = 1;
            } else if (count2 == 0) {
                candidate2 = num;
                count2 = 1;
            } else {
                count1--;
                count2--;
            }
        }

        count1 = 0;
        count2 = 0;

        for (int num : nums) {
            if (candidate1 != null && num == candidate1.intValue()) {
                count1++;
            } else if (candidate2 != null && num == candidate2.intValue()) {
                count2++;
            }
        }

        int n = nums.length;
        if (count1 > n / 3) {
            result.add(candidate1);
        }
        if (count2 > n / 3) {
            result.add(candidate2);
        }

        return result;
        
    }
}
