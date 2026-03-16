// Source: https://leetcode.com/problems/maximum-gap/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.
//
// You must write an algorithm that runs in linear time and uses linear extra space.
//
// Example:
// Input: nums = [3,6,9,1]
// Output: 3
// Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        
        int minNum = *min_element(nums.begin(), nums.end());
        int maxNum = *max_element(nums.begin(), nums.end());
        
        int bucketSize = max(1, (maxNum - minNum) / (n - 1));
        int bucketCount = (maxNum - minNum) / bucketSize + 1;
        
        vector<int> bucketMin(bucketCount, INT_MAX);
        vector<int> bucketMax(bucketCount, INT_MIN);
        vector<bool> bucketUsed(bucketCount, false);
        
        for (int num : nums) {
            int bucketIdx = (num - minNum) / bucketSize;
            bucketMin[bucketIdx] = min(bucketMin[bucketIdx], num);
            bucketMax[bucketIdx] = max(bucketMax[bucketIdx], num);
            bucketUsed[bucketIdx] = true;
        }
        
        int maxGap = 0;
        int prevMax = minNum;
        
        for (int i = 0; i < bucketCount; i++) {
            if (!bucketUsed[i]) continue;
            maxGap = max(maxGap, bucketMin[i] - prevMax);
            prevMax = bucketMax[i];
        }
        
        return maxGap;          
    }
};
