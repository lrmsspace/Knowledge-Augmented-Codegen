// Source: https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers and an integer k.
//
// For each subarray of nums, you can apply up to k operations on it. In each operation, you increment any element of the subarray by 1.
//
// Note that each subarray is considered independently, meaning changes made to one subarray do not persist to another.
//
// Return the number of subarrays that you can make non-decreasing ​​​​​after performing at most k operations.
//
// An array is said to be non-decreasing if each element is greater than or equal to its previous element, if it exists.
//
// Example:
// Input: nums = [6,3,1,2,4,4], k = 7
//
// Output: 17
//
// Explanation:
//
// Out of all 21 possible subarrays of nums, only the subarrays [6, 3, 1], [6, 3, 1, 2], [6, 3, 1, 2, 4] and [6, 3, 1, 2, 4, 4] cannot be made non-decreasing after applying up to k = 7 operations. Thus, the number of non-decreasing subarrays is 21 - 4 = 17.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//

class Solution {
    public long countNonDecreasingSubarrays(int[] nums, int k) {
        int n = nums.length;
        long totalSubarrays = ((long) n * (n + 1)) / 2;
        long invalidSubarrays = 0;

        for (int i = 0; i < n - 1; ) {
            if (nums[i] <= nums[i + 1]) {
                i++;
                continue;
            }

            int j = i + 1;
            long requiredOps = 0;

            while (j < n && nums[j - 1] > nums[j]) {
                requiredOps += nums[j - 1] - nums[j];
                if (requiredOps > k) {
                    break;
                }
                j++;
            }

            int len = j - i;
            invalidSubarrays += ((long) len * (len + 1)) / 2;

            i = j;
        }

        return totalSubarrays - invalidSubarrays;           
    }
}
