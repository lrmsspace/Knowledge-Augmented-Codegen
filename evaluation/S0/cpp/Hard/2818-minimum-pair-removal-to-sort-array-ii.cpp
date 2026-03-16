// Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums, you can perform the following operation any number of times:
//
//
// 	Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
// 	Replace the pair with their sum.
//
//
// Return the minimum number of operations needed to make the array non-decreasing.
//
// An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).
//
// Example:
// Input: nums = [5,2,3,1]
//
// Output: 2
//
// Explanation:
//
//
// 	The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
// 	The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
//
//
// The array nums became non-decreasing in two operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        vector<long long> prefixSums(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }

        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] >= nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        int maxLength = *max_element(dp.begin(), dp.end());
        return n - maxLength;           
    }
};
