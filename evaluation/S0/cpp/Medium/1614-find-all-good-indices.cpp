// Source: https://leetcode.com/problems/find-all-good-indices/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of size n and a positive integer k.
//
// We call an index i in the range k <= i < n - k good if the following conditions are satisfied:
//
//
// 	The k elements that are just before the index i are in non-increasing order.
// 	The k elements that are just after the index i are in non-decreasing order.
//
//
// Return an array of all good indices sorted in increasing order.
//
// Example:
// Input: nums = [2,1,1,1,3,4,1], k = 2
// Output: [2,3]
// Explanation: There are two good indices in the array:
// - Index 2. The subarray [2,1] is in non-increasing order, and the subarray [1,3] is in non-decreasing order.
// - Index 3. The subarray [1,1] is in non-increasing order, and the subarray [3,4] is in non-decreasing order.
// Note that the index 4 is not good because [4,1] is not non-decreasing.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n / 2
//

class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> left(n, 1), right(n, 1), result;

        // Fill left array
        for (int i = 1; i < n; ++i) {
            if (nums[i] <= nums[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }

        // Fill right array
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] <= nums[i + 1]) {
                right[i] = right[i + 1] + 1;
            }
        }

        // Find good indices
        for (int i = k; i <= n - k - 1; ++i) {
            if (left[i - 1] >= k && right[i + 1] >= k) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
