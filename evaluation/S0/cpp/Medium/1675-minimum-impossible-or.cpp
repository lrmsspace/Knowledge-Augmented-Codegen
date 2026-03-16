// Source: https://leetcode.com/problems/minimum-impossible-or/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// We say that an integer x is expressible from nums if there exist some integers 0 <= index1 < index2 < ... < indexk < nums.length for which nums[index1] | nums[index2] | ... | nums[indexk] = x. In other words, an integer is expressible if it can be written as the bitwise OR of some subsequence of nums.
//
// Return the minimum positive non-zero integer that is not expressible from nums.
//
// Example:
// Input: nums = [2,1]
// Output: 4
// Explanation: 1 and 2 are already present in the array. We know that 3 is expressible, since nums[0] | nums[1] = 2 | 1 = 3. Since 4 is not expressible, we return 4.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int result = 1;
        while (numSet.count(result)) {
            result <<= 1;
        }
        return result;          
    }
};
