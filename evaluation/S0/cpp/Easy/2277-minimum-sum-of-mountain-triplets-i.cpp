// Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of integers.
//
// A triplet of indices (i, j, k) is a mountain if:
//
//
// 	i < j < k
// 	nums[i] < nums[j] and nums[k] < nums[j]
//
//
// Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return -1.
//
// Example:
// Input: nums = [8,6,1,5,3]
// Output: 9
// Explanation: Triplet (2, 3, 4) is a mountain triplet of sum 9 since: 
// - 2 < 3 < 4
// - nums[2] < nums[3] and nums[4] < nums[3]
// And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.
//
// Constraints:
// 3 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        int minSum = INT_MAX;
        
        for (int j = 1; j < n - 1; ++j) {
            int leftMin = INT_MAX;
            int rightMin = INT_MAX;
            
            // Find the minimum element to the left of j that is less than nums[j]
            for (int i = 0; i < j; ++i) {
                if (nums[i] < nums[j]) {
                    leftMin = min(leftMin, nums[i]);
                }
            }
            
            // Find the minimum element to the right of j that is less than nums[j]
            for (int k = j + 1; k < n; ++k) {
                if (nums[k] < nums[j]) {
                    rightMin = min(rightMin, nums[k]);
                }
            }
            
            // If valid left and right elements are found, update the minimum sum
            if (leftMin != INT_MAX && rightMin != INT_MAX) {
                minSum = min(minSum, leftMin + nums[j] + rightMin);
            }
        }
        
        return (minSum == INT_MAX) ? -1 : minSum;           
    }
};
