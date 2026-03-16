// Source: https://leetcode.com/problems/maximum-equal-frequency/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers, return the longest possible length of an array prefix of nums, such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.
//
// If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).
//
// Example:
// Input: nums = [2,2,1,1,5,3,3,5]
// Output: 7
// Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4] = 5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int, int> count; // number -> frequency
        unordered_map<int, int> freq;  // frequency -> count of numbers with this frequency
        int res = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            int prevCount = count[num];
            count[num]++;
            int newCount = count[num];
            
            freq[prevCount]--;
            freq[newCount]++;
            
            // Check conditions
            bool condition1 = (freq.size() == 2 &&
                               ((freq.begin()->first == 1 && freq.begin()->second == 1) ||
                                (next(freq.begin())->first == 1 && next(freq.begin())->second == 1)));
            
            bool condition2 = (freq.size() == 2 &&
                               ((freq.begin()->first + 1 == next(freq.begin())->first && freq.begin()->second * freq.begin()->first + next(freq.begin())->second * next(freq.begin())->first == i + 1) ||
                                (next(freq.begin())->first + 1 == freq.begin()->first && next(freq.begin())->second * next(freq.begin())->first + freq.begin()->second * freq.begin()->first == i + 1)));
            
            bool condition3 = (freq.size() == 1 &&
                               (freq.begin()->first == 1 || freq.begin()->second == 1));
            
            if (condition1 || condition2 || condition3) {
                res = i + 1;
            }
        }
        
        return res;         
    }
};
