// Source: https://leetcode.com/problems/minimum-moves-to-make-array-complementary/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.
//
// The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.
//
// Return the minimum number of moves required to make nums complementary.
//
// Example:
// Input: nums = [1,2,4,3], limit = 4
// Output: 1
// Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
// nums[0] + nums[3] = 1 + 3 = 4.
// nums[1] + nums[2] = 2 + 2 = 4.
// nums[2] + nums[1] = 2 + 2 = 4.
// nums[3] + nums[0] = 3 + 1 = 4.
// Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	1 <= nums[i] <= limit <= 105
// 	n is even.
//

class Solution {
    public int minMoves(int[] nums, int limit) {
        int n = nums.length;
        int[] changes = new int[2 * limit + 2];

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = Math.min(a, b) + 1;
            int high = Math.max(a, b) + limit;

            changes[2] += 2; // default 2 moves for all sums
            changes[low] -= 1; // reduce to 1 move from low
            changes[a + b] -= 1; // reduce to 0 moves at a + b
            changes[a + b + 1] += 1; // back to 1 move after a + b
            changes[high + 1] += 1; // back to 2 moves after high
        }

        int minMoves = Integer.MAX_VALUE;
        int currentMoves = 0;

        for (int sum = 2; sum <= 2 * limit; sum++) {
            currentMoves += changes[sum];
            minMoves = Math.min(minMoves, currentMoves);
        }

        return minMoves;            
    }
}
