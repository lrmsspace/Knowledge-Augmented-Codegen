// Source: https://leetcode.com/problems/advantage-shuffle/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
//
// Return any permutation of nums1 that maximizes its advantage with respect to nums2.
//
// Example:
// Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
// Output: [2,11,7,15]
//
// Constraints:
// 1 <= nums1.length <= 105
// 	nums2.length == nums1.length
// 	0 <= nums1[i], nums2[i] <= 109
//

class Solution {
    public int[] advantageCount(int[] nums1, int[] nums2) {
        int n = nums1.length;
        int[] result = new int[n];
        boolean[] used = new boolean[n];

        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        Arrays.sort(nums1);
        Arrays.sort(indices, (a, b) -> Integer.compare(nums2[a], nums2[b]));

        int left = 0;
        int right = n - 1;

        for (int num : nums1) {
            if (num > nums2[indices[left]]) {
                result[indices[left]] = num;
                used[left] = true;
                left++;
            } else {
                result[indices[right]] = num;
                used[right] = true;
                right--;
            }
        }

        return result;          
    }
}
