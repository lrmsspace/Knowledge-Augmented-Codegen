// Source: https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// A split of an integer array is good if:
//
//
// 	The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
// 	The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
//
//
// Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,1,1]
// Output: 1
// Explanation: The only good way to split nums is [1] [1] [1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 104
//

class Solution {
public:
    int waysToSplit(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<long long> prefixSums(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSums[i + 1] = prefixSums[i] + nums[i];
        }

        int result = 0;
        for (int i = 1; i <= n - 2; ++i) {
            long long leftSum = prefixSums[i];

            // Binary search for the smallest j such that prefixSums[j] >= 2 * leftSum
            int low = i + 1, high = n - 1;
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (prefixSums[mid] >= 2 * leftSum) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            int firstValidJ = low;

            // Binary search for the largest j such that prefixSums[j] <= (totalSum + leftSum) / 2
            low = i + 1, high = n - 1;
            long long totalSum = prefixSums[n];
            while (low < high) {
                int mid = low + (high - low + 1) / 2;
                if (prefixSums[mid] <= (totalSum + leftSum) / 2) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            int lastValidJ = low;

            if (firstValidJ <= lastValidJ) {
                result = (result + (lastValidJ - firstValidJ + 1)) % MOD;
            }
        }

        return result;          
    }
};
