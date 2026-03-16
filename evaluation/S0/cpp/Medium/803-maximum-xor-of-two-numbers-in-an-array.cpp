// Source: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.
//
// Example:
// Input: nums = [3,10,5,25,2,8]
// Output: 28
// Explanation: The maximum result is 5 XOR 25 = 28.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	0 <= nums[i] <= 231 - 1
//

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int maxXOR = 0, mask = 0;
        for (int i = 31; i >= 0; --i) {
            mask |= (1 << i);
            unordered_set<int> prefixes;
            for (int num : nums) {
                prefixes.insert(num & mask);
            }

            int tentativeXOR = maxXOR | (1 << i);
            for (int prefix : prefixes) {
                if (prefixes.count(prefix ^ tentativeXOR)) {
                    maxXOR = tentativeXOR;
                    break;
                }
            }
        }
        return maxXOR;          
    }
};
