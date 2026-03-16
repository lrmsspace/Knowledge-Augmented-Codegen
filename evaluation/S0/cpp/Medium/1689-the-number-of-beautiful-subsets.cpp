// Source: https://leetcode.com/problems/the-number-of-beautiful-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of positive integers and a positive integer k.
//
// A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.
//
// Return the number of non-empty beautiful subsets of the array nums.
//
// A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [2,4,6], k = 2
// Output: 4
// Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
// It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
//
// Constraints:
// 1 <= nums.length <= 18
// 	1 <= nums[i], k <= 1000
//

class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int result = 0;

        function<void(int, int)> backtrack = [&](int index, int bitmask) {
            if (index == n) {
                if (bitmask != 0) {
                    result++;
                }
                return;
            }

            // Exclude current number
            backtrack(index + 1, bitmask);

            // Include current number if valid
            bool canInclude = true;
            for (int j = 0; j < index; ++j) {
                if ((bitmask & (1 << j)) && abs(nums[index] - nums[j]) == k) {
                    canInclude = false;
                    break;
                }
            }
            if (canInclude) {
                backtrack(index + 1, bitmask | (1 << index));
            }
        };

        backtrack(0, 0);
        return result;          
    }
};
