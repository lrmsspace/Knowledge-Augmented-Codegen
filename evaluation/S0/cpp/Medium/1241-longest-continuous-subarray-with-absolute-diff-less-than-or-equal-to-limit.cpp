// Source: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
//
// Example:
// Input: nums = [8,2,4,7], limit = 4
// Output: 2 
// Explanation: All subarrays are: 
// [8] with maximum absolute diff |8-8| = 0 <= 4.
// [8,2] with maximum absolute diff |8-2| = 6 > 4. 
// [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
// [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
// [2] with maximum absolute diff |2-2| = 0 <= 4.
// [2,4] with maximum absolute diff |2-4| = 2 <= 4.
// [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
// [4] with maximum absolute diff |4-4| = 0 <= 4.
// [4,7] with maximum absolute diff |4-7| = 3 <= 4.
// [7] with maximum absolute diff |7-7| = 0 <= 4. 
// Therefore, the size of the longest subarray is 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= limit <= 109
//

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> maxD, minD;
        int left = 0, result = 0;

        for (int right = 0; right < nums.size(); ++right) {
            while (!maxD.empty() && nums[right] > maxD.back()) {
                maxD.pop_back();
            }
            maxD.push_back(nums[right]);

            while (!minD.empty() && nums[right] < minD.back()) {
                minD.pop_back();
            }
            minD.push_back(nums[right]);

            while (maxD.front() - minD.front() > limit) {
                if (nums[left] == maxD.front()) {
                    maxD.pop_front();
                }
                if (nums[left] == minD.front()) {
                    minD.pop_front();
                }
                ++left;
            }

            result = max(result, right - left + 1);
        }

        return result;          
    }
};
