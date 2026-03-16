// Source: https://leetcode.com/problems/median-of-two-sorted-arrays/   |   Difficulty: Hard
//
// Problem Description:
// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
//
// The overall run time complexity should be O(log (m+n)).
//
// Example:
// Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
// Explanation: merged array = [1,2,3] and median is 2.
//
// Constraints:
// nums1.length == m
// 	nums2.length == n
// 	0 <= m <= 1000
// 	0 <= n <= 1000
// 	1 <= m + n <= 2000
// 	-106 <= nums1[i], nums2[i] <= 106
//

class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        int totalLength = m + n;
        boolean isEven = (totalLength % 2 == 0);
        
        int medianIndex1 = totalLength / 2;
        int medianIndex2 = isEven ? medianIndex1 - 1 : medianIndex1;
        
        int i = 0, j = 0, count = 0;
        int median1 = 0, median2 = 0;
        
        while (count <= medianIndex1) {
            int val;
            if (i < m && (j >= n || nums1[i] <= nums2[j])) {
                val = nums1[i++];
            } else {
                val = nums2[j++];
            }
            
            if (count == medianIndex2) {
                median2 = val;
            }
            if (count == medianIndex1) {
                median1 = val;
            }
            count++;
        }
        
        return isEven ? (median1 + median2) / 2.0 : median1;            
    }
}
