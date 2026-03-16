// Source: https://leetcode.com/problems/minimum-sum-of-squared-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive 0-indexed integer arrays nums1 and nums2, both of length n.
//
// The sum of squared difference of arrays nums1 and nums2 is defined as the sum of (nums1[i] - nums2[i])2 for each 0 <= i < n.
//
// You are also given two positive integers k1 and k2. You can modify any of the elements of nums1 by +1 or -1 at most k1 times. Similarly, you can modify any of the elements of nums2 by +1 or -1 at most k2 times.
//
// Return the minimum sum of squared difference after modifying array nums1 at most k1 times and modifying array nums2 at most k2 times.
//
// Note: You are allowed to modify the array elements to become negative integers.
//
// Example:
// Input: nums1 = [1,2,3,4], nums2 = [2,10,20,19], k1 = 0, k2 = 0
// Output: 579
// Explanation: The elements in nums1 and nums2 cannot be modified because k1 = 0 and k2 = 0. 
// The sum of square difference will be: (1 - 2)2 + (2 - 10)2 + (3 - 20)2 + (4 - 19)2 = 579.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	0 <= nums1[i], nums2[i] <= 105
// 	0 <= k1, k2 <= 109
//

class Solution {
    public long minSumSquareDiff(int[] nums1, int[] nums2, int k1, int k2) {
        int n = nums1.length;
        long k = (long) k1 + k2;

        int[] diffCount = new int[100001];
        for (int i = 0; i < n; i++) {
            int diff = Math.abs(nums1[i] - nums2[i]);
            diffCount[diff]++;
        }

        for (int d = 100000; d > 0 && k > 0; d--) {
            if (diffCount[d] == 0) {
                continue;
            }

            long totalDiffsAtD = diffCount[d];
            if (totalDiffsAtD <= k) {
                diffCount[d - 1] += diffCount[d];
                k -= totalDiffsAtD;
                diffCount[d] = 0;
            } else {
                long fullReductions = k / totalDiffsAtD;
                long remainder = k % totalDiffsAtD;

                diffCount[d] -= totalDiffsAtD;
                diffCount[d - (int) fullReductions] += (int) (totalDiffsAtD - remainder);
                if (d - (int) fullReductions - 1 >= 0) {
                    diffCount[d - (int) fullReductions - 1] += (int) remainder;
                }
                k = 0;
            }
        }

        long result = 0;
        for (int d = 1; d <= 100000; d++) {
            if (diffCount[d] > 0) {
                result += (long) diffCount[d] * d * d;
            }
        }

        return result;          
    }
}
