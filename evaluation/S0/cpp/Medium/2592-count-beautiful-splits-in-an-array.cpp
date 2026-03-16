// Source: https://leetcode.com/problems/count-beautiful-splits-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums.
//
// A split of an array nums is beautiful if:
//
//
// 	The array nums is split into three subarrays: nums1, nums2, and nums3, such that nums can be formed by concatenating nums1, nums2, and nums3 in that order.
// 	The subarray nums1 is a prefix of nums2 OR nums2 is a prefix of nums3.
//
//
// Return the number of ways you can make this split.
//
// Example:
// Input: nums = [1,1,2,1]
//
// Output: 2
//
// Explanation:
//
// The beautiful splits are:
//
//
// 	A split with nums1 = [1], nums2 = [1,2], nums3 = [1].
// 	A split with nums1 = [1], nums2 = [1], nums3 = [2,1].
//
// Constraints:
// 1 <= nums.length <= 5000
// 	0 <= nums[i] <= 50
//

class Solution {
public:
    int beautifulSplits(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<int> prefixCount(n, 0);
        vector<int> suffixCount(n, 0);
        unordered_map<int, int> countMap;

        // Count distinct elements in prefix
        for (int i = 0; i < n; ++i) {
            countMap[nums[i]]++;
            prefixCount[i] = countMap.size();
        }

        countMap.clear();

        // Count distinct elements in suffix
        for (int i = n - 1; i >= 0; --i) {
            countMap[nums[i]]++;
            suffixCount[i] = countMap.size();
        }

        int result = 0;

        // Check for beautiful splits
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                if (prefixCount[i] == prefixCount[j] || prefixCount[j] == suffixCount[j + 1]) {
                    result = (result + 1) % MOD;
                }
            }
        }

        return result;          
    }
};
