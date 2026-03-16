// Source: https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of integers nums.
//
// A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j - 1] + 1. In particular, the prefix consisting only of nums[0] is sequential.
//
// Return the smallest integer x missing from nums such that x is greater than or equal to the sum of the longest sequential prefix.
//
// Example:
// Input: nums = [1,2,3,2,5]
// Output: 6
// Explanation: The longest sequential prefix of nums is [1,2,3] with a sum of 6. 6 is not in the array, therefore 6 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = nums.size();
        int prefixSum = 0;
        int expectedNum = nums[0];

        for (int i = 0; i < n; ++i) {
            if (nums[i] == expectedNum) {
                prefixSum += nums[i];
                expectedNum++;
            } else {
                break;
            }
        }

        unordered_set<int> numSet(nums.begin(), nums.end());
        int missingInteger = prefixSum;

        while (numSet.count(missingInteger)) {
            missingInteger++;
        }

        return missingInteger;          
    }
};
