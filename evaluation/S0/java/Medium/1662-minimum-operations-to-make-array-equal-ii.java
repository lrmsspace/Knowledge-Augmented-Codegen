// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of equal length n and an integer k. You can perform the following operation on nums1:
//
//
// 	Choose two indexes i and j and increment nums1[i] by k and decrement nums1[j] by k. In other words, nums1[i] = nums1[i] + k and nums1[j] = nums1[j] - k.
//
//
// nums1 is said to be equal to nums2 if for all indices i such that 0 <= i < n, nums1[i] == nums2[i].
//
// Return the minimum number of operations required to make nums1 equal to nums2. If it is impossible to make them equal, return -1.
//
// Example:
// Input: nums1 = [4,3,1,4], nums2 = [1,3,7,1], k = 3
// Output: 2
// Explanation: In 2 operations, we can transform nums1 to nums2.
// 1st operation: i = 2, j = 0. After applying the operation, nums1 = [1,3,4,4].
// 2nd operation: i = 2, j = 3. After applying the operation, nums1 = [1,3,7,1].
// One can prove that it is impossible to make arrays equal in fewer operations.
//
// Constraints:
// n == nums1.length == nums2.length
// 	2 <= n <= 105
// 	0 <= nums1[i], nums2[j] <= 109
// 	0 <= k <= 105
//

class Solution {
    public long minOperations(int[] nums1, int[] nums2, int k) {
        if (k == 0) {
            for (int i = 0; i < nums1.length; i++) {
                if (nums1[i] != nums2[i]) {
                    return -1;
                }
            }
            return 0;
        }

        long increment = 0;
        long decrement = 0;

        for (int i = 0; i < nums1.length; i++) {
            int diff = nums2[i] - nums1[i];
            if (diff % k != 0) {
                return -1;
            }
            if (diff > 0) {
                increment += diff / k;
            } else {
                decrement += (-diff) / k;
            }
        }

        return increment == decrement ? increment : -1;         
    }
}
