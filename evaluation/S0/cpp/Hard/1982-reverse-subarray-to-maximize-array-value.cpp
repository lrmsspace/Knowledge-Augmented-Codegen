// Source: https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The value of this array is defined as the sum of |nums[i] - nums[i + 1]| for all 0 <= i < nums.length - 1.
//
// You are allowed to select any subarray of the given array and reverse it. You can perform this operation only once.
//
// Find maximum possible value of the final array.
//
// Example:
// Input: nums = [2,3,1,5,4]
// Output: 10
// Explanation: By reversing the subarray [3,1,5] the array becomes [2,5,1,3,4] whose value is 10.
//
// Constraints:
// 2 <= nums.length <= 3 * 104
// 	-105 <= nums[i] <= 105
// 	The answer is guaranteed to fit in a 32-bit integer.
//

class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        int originalValue = 0;
        for (int i = 0; i < n - 1; i++) {
            originalValue += abs(nums[i] - nums[i + 1]);
        }
        
        int maxGain = 0;
        
        // Consider reversing subarray starting from index 0
        for (int j = 1; j < n - 1; j++) {
            int gain = abs(nums[0] - nums[j + 1]) - abs(nums[j] - nums[j + 1]);
            maxGain = max(maxGain, gain);
        }
        
        // Consider reversing subarray ending at index n-1
        for (int i = 1; i < n - 1; i++) {
            int gain = abs(nums[n - 1] - nums[i - 1]) - abs(nums[i] - nums[i - 1]);
            maxGain = max(maxGain, gain);
        }
        
        // Consider reversing subarray in the middle
        int minPairMax = INT_MAX;
        int maxPairMin = INT_MIN;
        
        for (int i = 0; i < n - 1; i++) {
            int a = nums[i];
            int b = nums[i + 1];
            if (a > b) swap(a, b);
            minPairMax = min(minPairMax, b);
            maxPairMin = max(maxPairMin, a);
        }
        
        int gainMiddle = 2 * (max(0, maxPairMin - minPairMax));
        maxGain = max(maxGain, gainMiddle);
        
        return originalValue + maxGain;         
    }
};
