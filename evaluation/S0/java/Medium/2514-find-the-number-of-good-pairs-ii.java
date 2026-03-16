// Source: https://leetcode.com/problems/find-the-number-of-good-pairs-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given 2 integer arrays nums1 and nums2 of lengths n and m respectively. You are also given a positive integer k.
//
// A pair (i, j) is called good if nums1[i] is divisible by nums2[j] * k (0 <= i <= n - 1, 0 <= j <= m - 1).
//
// Return the total number of good pairs.
//
// Example:
// Input: nums1 = [1,3,4], nums2 = [1,3,4], k = 1
//
// Output: 5
//
// Explanation:
// The 5 good pairs are (0, 0), (1, 0), (1, 1), (2, 0), and (2, 2).
//
// Constraints:
// 1 <= n, m <= 105
// 	1 <= nums1[i], nums2[j] <= 106
// 	1 <= k <= 103
//

class Solution {
    public long numberOfPairs(int[] nums1, int[] nums2, int k) {
        long count = 0;
        int maxNum = 1000000;
        int[] freq = new int[maxNum + 1];

        for (int num : nums2) {
            freq[num]++;
        }

        for (int num1 : nums1) {
            for (int multiple = k; multiple <= maxNum; multiple += k) {
                if (num1 < multiple) {
                    break;
                }
                if (num1 % multiple == 0) {
                    count += freq[multiple];
                }
            }
        }

        return count;           
    }
}
