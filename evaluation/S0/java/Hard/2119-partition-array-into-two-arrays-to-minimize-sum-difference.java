// Source: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
//
// Return the minimum possible absolute difference.
//
// Example:
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
//
// Constraints:
// 1 <= n <= 15
// 	nums.length == 2 * n
// 	-107 <= nums[i] <= 107
//

class Solution {
    public int minimumDifference(int[] nums) {
        int n = nums.length / 2;
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        Map<Integer, List<Integer>> leftSums = new HashMap<>();
        Map<Integer, List<Integer>> rightSums = new HashMap<>();

        computeSubsetSums(nums, 0, n, leftSums);
        computeSubsetSums(nums, n, 2 * n, rightSums);

        int minDiff = Integer.MAX_VALUE;
        for (int leftCount : leftSums.keySet()) {
            List<Integer> leftList = leftSums.get(leftCount);
            List<Integer> rightList = rightSums.get(n - leftCount);
            Collections.sort(rightList);

            for (int leftSum : leftList) {
                int target = totalSum / 2 - leftSum;
                int idx = Collections.binarySearch(rightList, target);
                if (idx < 0) {
                    idx = -(idx + 1);
                }

                if (idx < rightList.size()) {
                    int rightSum = rightList.get(idx);
                    int currentSum = leftSum + rightSum;
                    minDiff = Math.min(minDiff, Math.abs(totalSum - 2 * currentSum));
                }

                if (idx > 0) {
                    int rightSum = rightList.get(idx - 1);
                    int currentSum = leftSum + rightSum;
                    minDiff = Math.min(minDiff, Math.abs(totalSum - 2 * currentSum));
                }
            }
        }

        return minDiff;         
    }
}
