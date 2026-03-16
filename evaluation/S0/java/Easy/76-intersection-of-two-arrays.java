// Source: https://leetcode.com/problems/intersection-of-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
//
// Example:
// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2]
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	0 <= nums1[i], nums2[i] <= 1000
//

class Solution {
    public int[] intersection(int[] nums1, int[] nums2) {
        Set<Integer> set1 = new HashSet<>();
        Set<Integer> intersection = new HashSet<>();

        for (int num : nums1) {
            set1.add(num);
        }

        for (int num : nums2) {
            if (set1.contains(num)) {
                intersection.add(num);
            }
        }

        int[] result = new int[intersection.size()];
        int index = 0;
        for (int num : intersection) {
            result[index++] = num;
        }

        return result;          
    }
}
