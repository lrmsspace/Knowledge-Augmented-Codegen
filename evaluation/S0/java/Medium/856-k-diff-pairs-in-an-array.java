// Source: https://leetcode.com/problems/k-diff-pairs-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
//
// A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
//
//
// 	0 <= i, j < nums.length
// 	i != j
// 	|nums[i] - nums[j]| == k
//
//
// Notice that |val| denotes the absolute value of val.
//
// Example:
// Input: nums = [3,1,4,1,5], k = 2
// Output: 2
// Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
// Although we have two 1s in the input, we should only return the number of unique pairs.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-107 <= nums[i] <= 107
// 	0 <= k <= 107
//

class Solution {
    public int findPairs(int[] nums, int k) {
        if (k < 0) return 0;

        Map<Integer, Integer> numCounts = new HashMap<>();
        for (int num : nums) {
            numCounts.put(num, numCounts.getOrDefault(num, 0) + 1);
        }

        int pairCount = 0;
        for (Map.Entry<Integer, Integer> entry : numCounts.entrySet()) {
            int num = entry.getKey();
            int count = entry.getValue();

            if (k == 0) {
                if (count > 1) {
                    pairCount++;
                }
            } else {
                if (numCounts.containsKey(num + k)) {
                    pairCount++;
                }
            }
        }

        return pairCount;           
    }
}
