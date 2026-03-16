// Source: https://leetcode.com/problems/minimum-absolute-sum-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integer arrays nums1 and nums2, both of length n.
//
// The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
//
// You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
//
// Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
//
// |x| is defined as:
//
//
// 	x if x >= 0, or
// 	-x if x < 0.
//
// Example:
// Input: nums1 = [1,7,5], nums2 = [2,3,5]
// Output: 3
// Explanation: There are two possible optimal solutions:
// - Replace the second element with the first: [1,7,5] => [1,1,5], or
// - Replace the second element with the third: [1,7,5] => [1,5,5].
// Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
//
// Constraints:
// n == nums1.length
// 	n == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 105
//

class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        const int MOD = 1e9 + 7;
        int n = nums1.size();
        vector<int> sortedNums1 = nums1;
        sort(sortedNums1.begin(), sortedNums1.end());

        long long totalDiff = 0;
        int maxImprovement = 0;

        for (int i = 0; i < n; ++i) {
            int diff = abs(nums1[i] - nums2[i]);
            totalDiff = (totalDiff + diff) % MOD;

            // Binary search to find the closest value to nums2[i] in sortedNums1
            auto it = lower_bound(sortedNums1.begin(), sortedNums1.end(), nums2[i]);

            // Check the candidate found by lower_bound
            if (it != sortedNums1.end()) {
                int candidateDiff = abs(*it - nums2[i]);
                maxImprovement = max(maxImprovement, diff - candidateDiff);
            }

            // Check the previous candidate if it exists
            if (it != sortedNums1.begin()) {
                --it;
                int candidateDiff = abs(*it - nums2[i]);
                maxImprovement = max(maxImprovement, diff - candidateDiff);
            }
        }

        return (totalDiff - maxImprovement + MOD) % MOD;            
    }
};
