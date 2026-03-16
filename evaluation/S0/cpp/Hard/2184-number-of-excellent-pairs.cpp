// Source: https://leetcode.com/problems/number-of-excellent-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed positive integer array nums and a positive integer k.
//
// A pair of numbers (num1, num2) is called excellent if the following conditions are satisfied:
//
//
// 	Both the numbers num1 and num2 exist in the array nums.
// 	The sum of the number of set bits in num1 OR num2 and num1 AND num2 is greater than or equal to k, where OR is the bitwise OR operation and AND is the bitwise AND operation.
//
//
// Return the number of distinct excellent pairs.
//
// Two pairs (a, b) and (c, d) are considered distinct if either a != c or b != d. For example, (1, 2) and (2, 1) are distinct.
//
// Note that a pair (num1, num2) such that num1 == num2 can also be excellent if you have at least one occurrence of num1 in the array.
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: 5
// Explanation: The excellent pairs are the following:
// - (3, 3). (3 AND 3) and (3 OR 3) are both equal to (11) in binary. The total number of set bits is 2 + 2 = 4, which is greater than or equal to k = 3.
// - (2, 3) and (3, 2). (2 AND 3) is equal to (10) in binary, and (2 OR 3) is equal to (11) in binary. The total number of set bits is 1 + 2 = 3.
// - (1, 3) and (3, 1). (1 AND 3) is equal to (01) in binary, and (1 OR 3) is equal to (11) in binary. The total number of set bits is 1 + 2 = 3.
// So the number of excellent pairs is 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 60
//

class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        unordered_set<int> uniqueNums(nums.begin(), nums.end());
        vector<int> bitCounts;
        
        for (int num : uniqueNums) {
            int count = __builtin_popcount(num);
            bitCounts.push_back(count);
        }
        
        sort(bitCounts.begin(), bitCounts.end());
        
        long long result = 0;
        int n = bitCounts.size();
        
        for (int count : bitCounts) {
            int required = k - count;
            auto it = lower_bound(bitCounts.begin(), bitCounts.end(), required);
            result += (bitCounts.end() - it);
        }
        
        return result;          
    }
};
