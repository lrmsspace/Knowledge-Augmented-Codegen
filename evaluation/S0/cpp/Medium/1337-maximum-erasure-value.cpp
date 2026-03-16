// Source: https://leetcode.com/problems/maximum-erasure-value/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.
//
// Return the maximum score you can get by erasing exactly one subarray.
//
// An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).
//
// Example:
// Input: nums = [4,2,4,5,6]
// Output: 17
// Explanation: The optimal subarray here is [2,4,5,6].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
//

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_set<int> seen;
        int left = 0, right = 0;
        int currentSum = 0;
        int maxSum = 0;
        int n = nums.size();

        while (right < n) {
            if (seen.find(nums[right]) == seen.end()) {
                // Expand the window to the right
                seen.insert(nums[right]);
                currentSum += nums[right];
                maxSum = max(maxSum, currentSum);
                right++;
            } else {
                // Shrink the window from the left
                seen.erase(nums[left]);
                currentSum -= nums[left];
                left++;
            }
        }

        return maxSum;          
    }
};
