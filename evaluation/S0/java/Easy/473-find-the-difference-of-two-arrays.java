// Source: https://leetcode.com/problems/find-the-difference-of-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given two 0-indexed integer arrays nums1 and nums2, return a list answer of size 2 where:
//
//
// 	answer[0] is a list of all distinct integers in nums1 which are not present in nums2.
// 	answer[1] is a list of all distinct integers in nums2 which are not present in nums1.
//
//
// Note that the integers in the lists may be returned in any order.
//
// Example:
// Input: nums1 = [1,2,3], nums2 = [2,4,6]
// Output: [[1,3],[4,6]]
// Explanation:
// For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] = 1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].
// For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] = 4 and nums2[2] = 6 are not present in nums1. Therefore, answer[1] = [4,6].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	-1000 <= nums1[i], nums2[i] <= 1000
//

class Solution {
    public List<List<Integer>> findDifference(int[] nums1, int[] nums2) {
        Set<Integer> set1 = new HashSet<>();
        Set<Integer> set2 = new HashSet<>();

        for (int num : nums1) {
            set1.add(num);
        }

        for (int num : nums2) {
            set2.add(num);
        }

        List<Integer> diff1 = new ArrayList<>();
        for (int num : set1) {
            if (!set2.contains(num)) {
                diff1.add(num);
            }
        }

        List<Integer> diff2 = new ArrayList<>();
        for (int num : set2) {
            if (!set1.contains(num)) {
                diff2.add(num);
            }
        }

        List<List<Integer>> result = new ArrayList<>();
        result.add(diff1);
        result.add(diff2);

        return result;          
    }
}
