// Source: https://leetcode.com/problems/count-of-smaller-numbers-after-self/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].
//
// Example:
// Input: nums = [5,2,6,1]
// Output: [2,1,1,0]
// Explanation:
// To the right of 5 there are 2 smaller elements (2 and 1).
// To the right of 2 there is only 1 smaller element (1).
// To the right of 6 there is 1 smaller element (1).
// To the right of 1 there is 0 smaller element.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 0);
        vector<int> sorted;

        for (int i = n - 1; i >= 0; i--) {
            int pos = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin();
            result[i] = pos;
            sorted.insert(sorted.begin() + pos, nums[i]);
        }

        return result;          
    }
};
