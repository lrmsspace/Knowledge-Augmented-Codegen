// Source: https://leetcode.com/problems/make-sum-divisible-by-p/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
//
// Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
//
// A subarray is defined as a contiguous block of elements in the array.
//
// Example:
// Input: nums = [3,1,4,2], p = 6
// Output: 1
// Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= p <= 109
//

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long total = 0;
        for (int num : nums) {
            total = (total + num) % p;
        }
        if (total == 0) return 0;

        unordered_map<long long, int> prefixModIndex;
        prefixModIndex[0] = -1; // Handle the case where the subarray starts from index 0
        long long currentMod = 0;
        int minLength = nums.size();

        for (int i = 0; i < nums.size(); ++i) {
            currentMod = (currentMod + nums[i]) % p;
            long long targetMod = (currentMod - total + p) % p;

            if (prefixModIndex.find(targetMod) != prefixModIndex.end()) {
                minLength = min(minLength, i - prefixModIndex[targetMod]);
            }
            prefixModIndex[currentMod] = i;
        }

        return minLength == nums.size() ? -1 : minLength;           
    }
};
