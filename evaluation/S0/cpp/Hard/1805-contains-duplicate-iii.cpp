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
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        if (indexDiff <= 0 || valueDiff < 0) return false;
        
        map<long long, long long> buckets;
        long long bucketSize = (long long)valueDiff + 1;
        
        for (int i = 0; i < nums.size(); i++) {
            long long num = (long long)nums[i];
            long long bucketId = num / bucketSize;
            if (num < 0) bucketId--;  // Adjust for negative numbers
            
            // Check current bucket
            if (buckets.count(bucketId)) return true;
            
            // Check previous bucket
            if (buckets.count(bucketId - 1) && abs(num - buckets[bucketId - 1]) <= valueDiff) return true;
            
            // Check next bucket
            if (buckets.count(bucketId + 1) && abs(num - buckets[bucketId + 1]) <= valueDiff) return true;
            
            // Insert into current bucket
            buckets[bucketId] = num;
            
            // Maintain the sliding window of size indexDiff
            if (i >= indexDiff) {
                long long oldNum = (long long)nums[i - indexDiff];
                long long oldBucketId = oldNum / bucketSize;
                if (oldNum < 0) oldBucketId--;
                buckets.erase(oldBucketId);
            }
        }
        
        return false;           
    }
};
