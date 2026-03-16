// Source: https://leetcode.com/problems/find-common-elements-between-two-arrays/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of sizes n and m, respectively. Calculate the following values:
//
//
// 	answer1 : the number of indices i such that nums1[i] exists in nums2.
// 	answer2 : the number of indices i such that nums2[i] exists in nums1.
//
//
// Return [answer1,answer2].
//
// Example:
// Input: nums1 = [2,3,2], nums2 = [1,2]
//
// Output: [2,1]
//
// Explanation:
//
// Constraints:
// n == nums1.length
// 	m == nums2.length
// 	1 <= n, m <= 100
// 	1 <= nums1[i], nums2[i] <= 100
//

class Solution {
    public int[] findIntersectionValues(int[] nums1, int[] nums2) {
        boolean[] existsInNums2 = new boolean[101];
        for (int num : nums2) {
            existsInNums2[num] = true;
        }

        int answer1 = 0;
        for (int num : nums1) {
            if (existsInNums2[num]) {
                answer1++;
            }
        }

        boolean[] existsInNums1 = new boolean[101];
        for (int num : nums1) {
            existsInNums1[num] = true;
        }

        int answer2 = 0;
        for (int num : nums2) {
            if (existsInNums1[num]) {
                answer2++;
            }
        }

        return new int[]{answer1, answer2};         
    }
}
