// Source: https://leetcode.com/problems/create-maximum-number/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.
//
// Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.
//
// Return an array of the k digits representing the answer.
//
// Example:
// Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
// Output: [9,8,6,5,3]
//
// Constraints:
// m == nums1.length
// 	n == nums2.length
// 	1 <= m, n <= 500
// 	0 <= nums1[i], nums2[i] <= 9
// 	1 <= k <= m + n
// 	nums1 and nums2 do not have leading zeros.
//

class Solution {
    public int[] maxNumber(int[] nums1, int[] nums2, int k) {
        int n = nums1.length, m = nums2.length;
        int[] ans = new int[k];
        for (int i = Math.max(0, k - m); i <= Math.min(k, n); i++) {
            int[] candidate = merge(maxArray(nums1, i), maxArray(nums2, k - i), k);
            if (greater(candidate, 0, ans, 0)) {
                ans = candidate;
            }
        }
        return ans;         
    }
}
