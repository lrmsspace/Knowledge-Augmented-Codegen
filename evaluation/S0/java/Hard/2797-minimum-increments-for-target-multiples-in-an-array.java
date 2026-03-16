// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//

class Solution {
    public int minimumIncrements(int[] nums, int[] target) {
        int n = nums.length;
        int m = target.length;
        Arrays.sort(nums);
        Arrays.sort(target);
        int res = Integer.MAX_VALUE;

        for (int mask = 0; mask < (1 << n); mask++) {
            if (Integer.bitCount(mask) != m) {
                continue;
            }
            int curr = 0;
            int tIdx = 0;
            boolean valid = true;

            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    if (nums[i] > target[tIdx]) {
                        valid = false;
                        break;
                    }
                    int increment = (target[tIdx] - nums[i]) % target[tIdx];
                    curr += increment;
                    tIdx++;
                }
            }

            if (valid) {
                res = Math.min(res, curr);
            }
        }

        return res;         
    }
}
