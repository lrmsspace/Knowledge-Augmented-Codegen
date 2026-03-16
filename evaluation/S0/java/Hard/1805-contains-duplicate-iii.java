// Source: https://leetcode.com/problems/contains-duplicate-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers indexDiff and valueDiff.
//
// Find a pair of indices (i, j) such that:
//
//
// 	i != j,
// 	abs(i - j) <= indexDiff.
// 	abs(nums[i] - nums[j]) <= valueDiff, and
//
//
// Return true if such pair exists or false otherwise.
//
// Example:
// Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
// Output: true
// Explanation: We can choose (i, j) = (0, 3).
// We satisfy the three conditions:
// i != j --> 0 != 3
// abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
// abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
//
// Constraints:
// 2 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= indexDiff <= nums.length
// 	0 <= valueDiff <= 109
//

class Solution {
    public boolean containsNearbyAlmostDuplicate(int[] nums, int indexDiff, int valueDiff) {
        if (valueDiff < 0 || indexDiff <= 0) return false;

        Map<Long, Long> buckets = new HashMap<>();
        long bucketSize = (long) valueDiff + 1;

        for (int i = 0; i < nums.length; i++) {
            long bucketId = getBucketId(nums[i], bucketSize);

            if (buckets.containsKey(bucketId)) {
                return true;
            }

            if (buckets.containsKey(bucketId - 1) && Math.abs(nums[i] - buckets.get(bucketId - 1)) <= valueDiff) {
                return true;
            }

            if (buckets.containsKey(bucketId + 1) && Math.abs(nums[i] - buckets.get(bucketId + 1)) <= valueDiff) {
                return true;
            }

            buckets.put(bucketId, (long) nums[i]);

            if (i >= indexDiff) {
                long oldBucketId = getBucketId(nums[i - indexDiff], bucketSize);
                buckets.remove(oldBucketId);
            }
        }

        return false;           
    }
}
