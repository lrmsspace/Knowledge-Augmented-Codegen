// Source: https://leetcode.com/problems/find-the-integer-added-to-array-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2.
//
// From nums1 two elements have been removed, and all other elements have been increased (or decreased in the case of negative) by an integer, represented by the variable x.
//
// As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the same integers with the same frequencies.
//
// Return the minimum possible integer x that achieves this equivalence.
//
// Example:
// Input: nums1 = [4,20,16,12,8], nums2 = [14,18,10]
//
// Output: -2
//
// Explanation:
//
// After removing elements at indices [0,4] and adding -2, nums1 becomes [18,14,10].
//
// Constraints:
// 3 <= nums1.length <= 200
// 	nums2.length == nums1.length - 2
// 	0 <= nums1[i], nums2[i] <= 1000
// 	The test cases are generated in a way that there is an integer x such that nums1 can become equal to nums2 by removing two elements and adding x to each element of nums1.
//

class Solution {
    public int minimumAddedInteger(int[] nums1, int[] nums2) {
        Arrays.sort(nums1);
        Arrays.sort(nums2);
        int n = nums1.length;
        int m = nums2.length;
        int minX = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x = nums2[0] - nums1[(0 < i) ? 0 : (0 < j) ? 1 : 2];
                boolean isValid = true;
                int index1 = 0, index2 = 0;

                while (index2 < m) {
                    if (index1 == i || index1 == j) {
                        index1++;
                        continue;
                    }
                    if (nums1[index1] + x != nums2[index2]) {
                        isValid = false;
                        break;
                    }
                    index1++;
                    index2++;
                }

                if (isValid) {
                    minX = Math.min(minX, x);
                }
            }
        }

        return minX;            
    }
}
