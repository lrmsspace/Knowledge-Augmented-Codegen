// Source: https://leetcode.com/problems/minimum-sum-of-mountain-triplets-ii/   |   Difficulty: Medium
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
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 108
//

class Solution {
public:
    int minimumSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> leftMin(n, INT_MAX);
        set<int> leftSet;

        // Find the minimum element to the left of each index that is less than nums[i]
        for (int i = 0; i < n; ++i) {
            auto it = leftSet.lower_bound(nums[i]);
            if (it != leftSet.begin()) {
                --it;
                leftMin[i] = *it;
            }
            leftSet.insert(nums[i]);
        }

        int minSum = INT_MAX;
        set<int> rightSet;

        // Traverse from right to left to find the minimum mountain triplet sum
        for (int i = n - 1; i >= 0; --i) {
            auto it = rightSet.lower_bound(nums[i]);
            if (it != rightSet.end() && leftMin[i] != INT_MAX) {
                minSum = min(minSum, leftMin[i] + nums[i] + *it);
            }
            rightSet.insert(nums[i]);
        }

        return minSum == INT_MAX ? -1 : minSum;         
    }
};
