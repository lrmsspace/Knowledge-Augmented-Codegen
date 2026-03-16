// Source: https://leetcode.com/problems/maximum-size-of-a-set-after-removals/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of even length n.
//
// You must remove n / 2 elements from nums1 and n / 2 elements from nums2. After the removals, you insert the remaining elements of nums1 and nums2 into a set s.
//
// Return the maximum possible size of the set s.
//
// Example:
// Input: nums1 = [1,2,1,2], nums2 = [1,1,1,1]
// Output: 2
// Explanation: We remove two occurences of 1 from nums1 and nums2. After the removals, the arrays become equal to nums1 = [2,2] and nums2 = [1,1]. Therefore, s = {1,2}.
// It can be shown that 2 is the maximum possible size of the set s after the removals.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 2 * 104
// 	n is even.
// 	1 <= nums1[i], nums2[i] <= 109
//

class Solution {
    public int maximumSetSize(int[] nums1, int[] nums2) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        int n = nums1.length;

        for (int num : nums1) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        for (int num : nums2) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        int maxPossibleSize = 0;
        for (int freq : freqMap.values()) {
            if (freq > 0) {
                maxPossibleSize++;
            }
        }

        return Math.min(maxPossibleSize, n);            
    }
}
