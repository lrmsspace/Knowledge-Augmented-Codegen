// Source: https://leetcode.com/problems/count-increasing-quadruplets/   |   Difficulty: Hard
//
// Problem Description:
// Given a 0-indexed integer array nums of size n containing all numbers from 1 to n, return the number of increasing quadruplets.
//
// A quadruplet (i, j, k, l) is increasing if:
//
//
// 	0 <= i < j < k < l < n, and
// 	nums[i] < nums[k] < nums[j] < nums[l].
//
// Example:
// Input: nums = [1,3,2,4,5]
// Output: 2
// Explanation: 
// - When i = 0, j = 1, k = 2, and l = 3, nums[i] < nums[k] < nums[j] < nums[l].
// - When i = 0, j = 1, k = 2, and l = 4, nums[i] < nums[k] < nums[j] < nums[l]. 
// There are no other quadruplets, so we return 2.
//
// Constraints:
// 4 <= nums.length <= 4000
// 	1 <= nums[i] <= nums.length
// 	All the integers of nums are unique. nums is a permutation.
//

class Solution {
    public long countQuadruplets(int[] nums) {
        int n = nums.length;
        long result = 0;

        for (int j = 1; j < n - 2; j++) {
            for (int k = j + 1; k < n - 1; k++) {
                if (nums[j] <= nums[k]) {
                    continue;
                }

                long countI = 0;
                for (int i = 0; i < j; i++) {
                    if (nums[i] < nums[k]) {
                        countI++;
                    }
                }

                long countL = 0;
                for (int l = k + 1; l < n; l++) {
                    if (nums[l] > nums[j]) {
                        countL++;
                    }
                }

                result += countI * countL;
            }
        }

        return result;          
    }
}
