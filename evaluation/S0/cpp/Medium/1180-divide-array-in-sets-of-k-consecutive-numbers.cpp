// Source: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.
//
// Return true if it is possible. Otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,3,4,4,5,6], k = 4
// Output: true
// Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as 846: https://leetcode.com/problems/hand-of-straights/
//

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k != 0) return false;

        unordered_map<int, int> countMap;
        for (int num : nums) {
            countMap[num]++;
        }

        sort(nums.begin(), nums.end());

        for (int num : nums) {
            if (countMap[num] == 0) continue;

            for (int i = 0; i < k; ++i) {
                if (countMap[num + i] == 0) {
                    return false;
                }
                countMap[num + i]--;
            }
        }

        return true;            
    }
};
