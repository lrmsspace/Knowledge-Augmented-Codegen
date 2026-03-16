// Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// A special triplet is defined as a triplet of indices (i, j, k) such that:
//
//
// 	0 <= i < j < k < n, where n = nums.length
// 	nums[i] == nums[j] * 2
// 	nums[k] == nums[j] * 2
//
//
// Return the total number of special triplets in the array.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [6,3,6]
//
// Output: 1
//
// Explanation:
//
// The only special triplet is (i, j, k) = (0, 1, 2), where:
//
//
// 	nums[0] = 6, nums[1] = 3, nums[2] = 6
// 	nums[0] = nums[1] * 2 = 3 * 2 = 6
// 	nums[2] = nums[1] * 2 = 3 * 2 = 6
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//

class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        unordered_map<int, long long> countBefore, countAfter;
        for (int num : nums) {
            countAfter[num]++;
        }

        long long result = 0;
        for (int j = 0; j < nums.size(); ++j) {
            int num = nums[j];
            countAfter[num]--;

            if (num % 2 == 0) {
                int half = num / 2;
                int doubleNum = num * 2;
                if (countBefore.count(half) && countAfter.count(doubleNum)) {
                    result = (result + countBefore[half] * countAfter[doubleNum]) % MOD;
                }
            }

            countBefore[num]++;
        }

        return static_cast<int>(result);            
    }
};
