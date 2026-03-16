// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of n positive integers.
//
// The array nums is called alternating if:
//
//
// 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
// 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
//
//
// In one operation, you can choose an index i and change nums[i] into any positive integer.
//
// Return the minimum number of operations required to make the array alternating.
//
// Example:
// Input: nums = [3,1,3,2,4,3]
// Output: 3
// Explanation:
// One way to make the array alternating is by converting it to [3,1,3,1,3,1].
// The number of operations required in this case is 3.
// It can be proven that it is not possible to make the array alternating in less than 3 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public int minimumOperations(int[] nums) {
        int n = nums.length;

        // Frequency maps for even and odd indexed elements
        Map<Integer, Integer> evenFreq = new HashMap<>();
        Map<Integer, Integer> oddFreq = new HashMap<>();

        // Populate frequency maps
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                evenFreq.put(nums[i], evenFreq.getOrDefault(nums[i], 0) + 1);
            } else {
                oddFreq.put(nums[i], oddFreq.getOrDefault(nums[i], 0) + 1);
            }
        }

        // Get the two most common elements and their frequencies for even and odd indexed elements
        int[] evenTop = getTopTwo(evenFreq);
        int[] oddTop = getTopTwo(oddFreq);

        // Calculate minimum operations
        if (evenTop[0] != oddTop[0]) {
            return n - evenTop[1] - oddTop[1];
        } else {
            return Math.min(n - evenTop[1] - oddTop[3], n - evenTop[3] - oddTop[1]);
        }           
    }
}
