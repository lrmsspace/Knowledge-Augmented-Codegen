// Source: https://leetcode.com/problems/sum-of-subarray-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The range of a subarray of nums is the difference between the largest and smallest element in the subarray.
//
// Return the sum of all subarray ranges of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 4
// Explanation: The 6 subarrays of nums are the following:
// [1], range = largest - smallest = 1 - 1 = 0 
// [2], range = 2 - 2 = 0
// [3], range = 3 - 3 = 0
// [1,2], range = 2 - 1 = 1
// [2,3], range = 3 - 2 = 1
// [1,2,3], range = 3 - 1 = 2
// So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow-up: Could you find a solution with O(n) time complexity?
//

class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        long long totalMax = 0, totalMin = 0;

        // Calculate contribution as maximum
        {
            vector<int> left(n), right(n);
            stack<int> stk;

            for (int i = 0; i < n; ++i) {
                while (!stk.empty() && nums[stk.top()] < nums[i]) {
                    stk.pop();
                }
                left[i] = stk.empty() ? -1 : stk.top();
                stk.push(i);
            }

            stk = stack<int>();
            for (int i = n - 1; i >= 0; --i) {
                while (!stk.empty() && nums[stk.top()] <= nums[i]) {
                    stk.pop();
                }
                right[i] = stk.empty() ? n : stk.top();
                stk.push(i);
            }

            for (int i = 0; i < n; ++i) {
                totalMax += (long long)(i - left[i]) * (right[i] - i) * nums[i];
            }
        }

        // Calculate contribution as minimum
        {
            vector<int> left(n), right(n);
            stack<int> stk;

            for (int i = 0; i < n; ++i) {
                while (!stk.empty() && nums[stk.top()] > nums[i]) {
                    stk.pop();
                }
                left[i] = stk.empty() ? -1 : stk.top();
                stk.push(i);
            }

            stk = stack<int>();
            for (int i = n - 1; i >= 0; --i) {
                while (!stk.empty() && nums[stk.top()] >= nums[i]) {
                    stk.pop();
                }
                right[i] = stk.empty() ? n : stk.top();
                stk.push(i);
            }

            for (int i = 0; i < n; ++i) {
                totalMin += (long long)(i - left[i]) * (right[i] - i) * nums[i];
            }
        }

        return totalMax - totalMin;         
    }
};
