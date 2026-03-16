// Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of integers.
//
// A triplet of indices (i, j, k) is a mountain if:
//
//
// 	i < j < k
// 	nums[i] < nums[j] and nums[k] < nums[j]
//
//
// Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
//
// Example:
// Input: nums = [8,6,1,5,3]
// Output: 9
// Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
// - 2 < 3 < 4
// - nums[2] < nums[3] and nums[4] < nums[3]
// And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 108
//

class Solution {
    public int minimumSum(int[] nums) {
        int n = nums.length;
        int[] leftMin = new int[n];
        int[] rightMin = new int[n];
        TreeSet<Integer> leftSet = new TreeSet<>();
        TreeSet<Integer> rightSet = new TreeSet<>();

        // Fill leftMin array
        for (int i = 0; i < n; i++) {
            Integer smaller = leftSet.lower(nums[i]);
            leftMin[i] = (smaller != null) ? smaller : Integer.MAX_VALUE;
            leftSet.add(nums[i]);
        }

        // Fill rightMin array
        for (int i = n - 1; i >= 0; i--) {
            Integer smaller = rightSet.lower(nums[i]);
            rightMin[i] = (smaller != null) ? smaller : Integer.MAX_VALUE;
            rightSet.add(nums[i]);
        }

        // Calculate minimum mountain triplet sum
        int minSum = Integer.MAX_VALUE;
        for (int j = 1; j < n - 1; j++) {
            if (leftMin[j] != Integer.MAX_VALUE && rightMin[j] != Integer.MAX_VALUE) {
                int currentSum = leftMin[j] + nums[j] + rightMin[j];
                minSum = Math.min(minSum, currentSum);
            }
        }

        return (minSum == Integer.MAX_VALUE) ? -1 : minSum;         
    }
}
